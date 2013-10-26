#include <QApplication>
#include "hybridServer.h"

int main(int argc, char **argv){
  QApplication app(argc, argv);

  HybridServer hs;

  return app.exec();
}
