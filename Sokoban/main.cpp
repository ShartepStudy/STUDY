#include "sokoban_app.h"

void main() {
   sokoban::SokobanApp app;
   app.Init("level_6.dat");
   app.Run();
}