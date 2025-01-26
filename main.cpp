#include "App.h"
#include <locale>

int main() 
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    App app;
    app.run();
    return 0;
}
