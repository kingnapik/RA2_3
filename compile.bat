@echo off
echo === Compilando Analisador Sintatico ===
echo.

g++ -std=c++17 -Wall -O2 -c gramatica.cpp -o gramatica.o
if errorlevel 1 goto error

g++ -std=c++17 -Wall -O2 -c parser.cpp -o parser.o
if errorlevel 1 goto error

g++ -std=c++17 -Wall -O2 -c arvore.cpp -o arvore.o
if errorlevel 1 goto error

g++ -std=c++17 -Wall -O2 -c leitor.cpp -o leitor.o
if errorlevel 1 goto error

g++ -std=c++17 -Wall -O2 -c main.cpp -o main.o
if errorlevel 1 goto error

g++ -std=c++17 -Wall -O2 -o AnalisadorSintatico.exe main.o gramatica.o parser.o arvore.o leitor.o
if errorlevel 1 goto error

echo.
echo === Compilacao concluida com sucesso! ===
echo.
echo Execute com:
echo   .\AnalisadorSintatico.exe teste1.txt
echo.
goto end

:error
echo.
echo === ERRO na compilacao ===
pause
exit /b 1

:end