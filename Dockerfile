# Debian bullseye-slimをベースイメージに
FROM debian:bullseye-slim

# 必要なパッケージをインストール
RUN apt update && apt-get update && apt-get install -y \
    g++ \
    make \
    cmake \
    wget \
    lcov \
    doxygen \
    graphviz \
    cppcheck \
    vim \
    python3 \
    python3-pip \
    libtinyxml2-dev \
    && rm -rf /var/lib/apt/lists/*

# Google Test v1.8.0のインストール
RUN wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz \
    && tar -xzf release-1.8.0.tar.gz \
    && cd googletest-release-1.8.0 \
    && mkdir build && cd build \
    && cmake -DCMAKE_CXX_FLAGS="-std=c++98" -DBUILD_GMOCK=ON -DBUILD_GTEST=ON -DCMAKE_CXX_STANDARD=98 .. \
    && make && make install \
    && ldconfig \
    && cd ../.. && rm -rf googletest-release-1.8.0 release-1.8.0.tar.gz
# Cppcheck最新版
RUN wget https://github.com/danmar/cppcheck/archive/refs/tags/2.15.0.tar.gz \
    && tar -xzf 2.15.0.tar.gz \
    && cd cppcheck-2.15.0 \
    && mkdir build && cd build \
    && cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DUSE_BUNDLED_TINYXML2=OFF .. \
    && make && make install \
    && mkdir -p /usr/local/share/Cppcheck/cfg \
    && cp -rv ../cfg/* /usr/local/share/Cppcheck/cfg/ \
    && ls -l /usr/local/share/Cppcheck/cfg/ \
    && cd ../.. && rm -rf cppcheck-2.15.0 2.15.0.tar.gz

# Python依存（cppcheck-htmlreport用）
RUN pip3 install pygments

# 作業ディレクトリを設定
WORKDIR /app

# エントリーポイント
CMD ["/bin/bash"]