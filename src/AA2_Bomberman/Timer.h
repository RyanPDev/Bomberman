#pragma once
#include <chrono>

class Timer
{
private:
	//Atributos
	std::chrono::time_point<std::chrono::system_clock> startTime;

public:
	//Inicializa el timer
	void Start();

	double ElapsedMilliSeconds();

	//Devuelve el tiempo transcurrido en segundos
	double ElapsedSeconds();
};