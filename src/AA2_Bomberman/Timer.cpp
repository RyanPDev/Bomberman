#include "Timer.h"

#pragma region Start
void Timer::Start()
{
	startTime = std::chrono::system_clock::now();
}
#pragma endregion Inicializa el timer

#pragma region Elapsed milliseconds
double Timer::ElapsedMilliSeconds()
{
	std::chrono::time_point<std::chrono::system_clock> endTime;

	endTime = std::chrono::system_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}
#pragma endregion Devuelve el tiempo transcurrido en milisegundos

#pragma region Elapsed seconds
double Timer::ElapsedSeconds()
{
	return ElapsedMilliSeconds() / 1000;
}
#pragma endregion Devuelve el tiempo transcurrido en segundos
