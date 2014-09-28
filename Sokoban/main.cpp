#include "sokoban_app.h"

void main() {
   sokoban::SokobanApp app;
   app.Init("level_8.dat");
   app.Run();
}