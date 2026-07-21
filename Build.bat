@echo off
echo ============================
echo Building Quiz Adventure...
echo ============================

g++ src/*.cpp -o QuizAdventure.exe -Iinclude -I/ucrt64/include -L/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

if %errorlevel%==0 (
    echo.
    echo ============================
    echo Build Successful!
    echo Starting Game...
    echo ============================
    QuizAdventure.exe
) else (
    echo.
    echo ============================
    echo Build Failed!
    echo ============================
)

pause