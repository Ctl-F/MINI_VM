#pragma once

#include <fstream>
#include <string>

enum class OutputType {
	STDIO,
	FILE,
	BOTH
};

class Logger {
public:
	Logger() = delete;

	void initLogging();
	static Logger& Get();
	void deinitLogging();

	void setOutputType(OutputType type);
	
	template<typename T> Logger& write(T message) {
		
	}

private:
	Logger();
	Logger(OutputType output);
	~Logger();

	OutputType m_mode;
	std::ofstream m_outputFile;

	static Logger* logger;
};

