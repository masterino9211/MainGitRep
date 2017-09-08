happyRUN: Game.o Tower.o Algorithm.o AudioPlayer.o Bezier.o Creep.o EmptyField.o Functor.o MenuElement.o PathField.o pugixml.o SimpleField.o Splash.o Timer.o Handler.o Layout.o main.o Map.o Menu.o TowerPriceDisplay.o Transitional.o UpgradeDisplay.o WaterField.o Wave.o
	g++ -Wall -std=c++11 -o happyRUN Game.o Tower.o Algorithm.o AudioPlayer.o Bezier.o Creep.o EmptyField.o Functor.o MenuElement.o PathField.o pugixml.o SimpleField.o Splash.o Timer.o Handler.o Layout.o main.o Map.o Menu.o TowerPriceDisplay.o Transitional.o UpgradeDisplay.o WaterField.o Wave.o -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-window -lsfml-system

Game.o : Timer.h SceneInterface.h Game.h DisplayInterface.h UpgradeDisplay.h AudioPlayer.h MenuElement.h pugixml.hpp Splash.h Menu.h Transitional.h Handler.h TowerPriceDisplay.h Game.cpp Map.h
	g++ -Wall -std=c++11 -c Game.cpp

Tower.o : Wave.h SimpleField.h SceneInterface.h Algorithm.h pugixml.hpp Creep.h Tower.cpp Tower.h TowerInterface.h
	g++ -Wall -std=c++11 -c Tower.cpp

Algorithm.o : Algorithm.h Algorithm.cpp
	g++ -Wall -std=c++11 -c Algorithm.cpp

AudioPlayer.o : pugixml.hpp AudioPlayer.h pugiconfig.hpp AudioPlayer.cpp
	g++ -Wall -std=c++11 -c AudioPlayer.cpp

Bezier.o : Algorithm.h Bezier.h Bezier.cpp
	g++ -Wall -std=c++11 -c Bezier.cpp

Creep.o : FieldInterface.h SimpleField.h SceneInterface.h Algorithm.h Creep.cpp pugixml.hpp Creep.h Tower.h Layout.h TowerInterface.h Bezier.h
	g++ -Wall -std=c++11 -c Creep.cpp

EmptyField.o : FieldInterface.h pugixml.hpp EmptyField.cpp EmptyField.h
	g++ -Wall -std=c++11 -c EmptyField.cpp

Functor.o : Functor.cpp Functor.h Handler.h
	g++ -Wall -std=c++11 -c Functor.cpp

MenuElement.o : AudioPlayer.h SceneInterface.h MenuElement.cpp MenuElement.h pugixml.hpp Handler.h Functor.h
	g++ -Wall -std=c++11 -c MenuElement.cpp

PathField.o : PathField.cpp FieldInterface.h PathField.h
	g++ -Wall -std=c++11 -c PathField.cpp

pugixml.o : pugixml.hpp pugixml.cpp pugiconfig.hpp
	g++ -Wall -std=c++11 -c pugixml.cpp

SimpleField.o : SimpleField.cpp SimpleField.h
	g++ -Wall -std=c++11 -c SimpleField.cpp

Splash.o : Algorithm.h Splash.h Splash.cpp Handler.h SceneInterface.h
	g++ -Wall -std=c++11 -c Splash.cpp

Timer.o : Timer.h Timer.cpp
	g++ -Wall -std=c++11 -c Timer.cpp

Handler.o : Handler.cpp Handler.h
	g++ -Wall -std=c++11 -c Handler.cpp

Layout.o : Wave.h PathField.h SceneInterface.h FieldInterface.h WaterField.h pugixml.hpp Creep.h Tower.h Layout.h Layout.cpp TowerInterface.h EmptyField.h SimpleField.h
	g++ -Wall -std=c++11 -c Layout.cpp

main.o : AudioPlayer.h Game.h Timer.h main.cpp SceneInterface.h
	g++ -Wall -std=c++11 -c main.cpp

Map.o : Wave.h SimpleField.h SceneInterface.h DisplayInterface.h UpgradeDisplay.h MenuElement.h pugixml.hpp Map.cpp Map.h Tower.h Handler.h Layout.h TowerPriceDisplay.h TowerInterface.h FieldInterface.h Menu.h
	g++ -Wall -std=c++11 -c Map.cpp

Menu.o : Menu.cpp SceneInterface.h MenuElement.h pugixml.hpp pugiconfig.hpp Menu.h
	g++ -Wall -std=c++11 -c Menu.cpp

TowerPriceDisplay.o : TowerPriceDisplay.h DisplayInterface.h TowerPriceDisplay.cpp
	g++ -Wall -std=c++11 -c TowerPriceDisplay.cpp

Transitional.o : Transitional.cpp Handler.h Transitional.h SceneInterface.h
	g++ -Wall -std=c++11 -c Transitional.cpp

UpgradeDisplay.o : TowerInterface.h DisplayInterface.h UpgradeDisplay.h UpgradeDisplay.cpp Tower.h
	g++ -Wall -std=c++11 -c UpgradeDisplay.cpp

WaterField.o : WaterField.cpp WaterField.h FieldInterface.h
	g++ -Wall -std=c++11 -c WaterField.cpp

Wave.o : Wave.h SimpleField.h SceneInterface.h pugixml.hpp Creep.h Tower.h Layout.h TowerInterface.h FieldInterface.h Wave.cpp
	g++ -Wall -std=c++11 -c Wave.cpp

clean:
	rm -rf *.o happyRUN

format:
	-astyle --style=kr --unpad-paren --indent=tab --align-reference=name --align-pointer=name *.cpp *.hpp
	-rm -rf *.orig