#ifndef LOGGER_H
#define LOGGER_H

class Logger {
public:
    Logger() { last_log[0] = '\0'; }
    virtual ~Logger() {} // 仮想デストラクタ
    virtual void log(const char* message); // 仮想関数
    virtual const char* get_last_log() const;
protected:
    char last_log[256];
};

#endif