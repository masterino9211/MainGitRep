happyRUN: Timer.o Functor.o SimpleField.o Map.o PathField.o TowerPriceDisplay.o Splash.o UpgradeDisplay.o pugixml.o Bezier.o Creep.o Menu.o MenuElement.o Game.o Wave.o EmptyField.o Layout.o Tower.o Transitional.o AudioPlayer.o Handler.o Algorithm.o WaterField.o main.o
	g++ -Wall -std=c++14 -o happyRUN Timer.o Functor.o SimpleField.o Map.o PathField.o TowerPriceDisplay.o Splash.o UpgradeDisplay.o pugixml.o Bezier.o Creep.o Menu.o MenuElement.o Game.o Wave.o EmptyField.o Layout.o Tower.o Transitional.o AudioPlayer.o Handler.o Algorithm.o WaterField.o main.o -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-window -lsfml-system

Timer.o : Timer.h Timer.cpp
	g++ -Wall -std=c++14 -c Timer.cpp

Functor.o : Functor.cpp Functor.h Handler.h
	g++ -Wall -std=c++14 -c Functor.cpp

SimpleField.o : SimpleField.cpp SimpleField.h
	g++ -Wall -std=c++14 -c SimpleField.cpp

Map.o : Wave.h SimpleField.h SceneInterface.h DisplayInterface.h UpgradeDisplay.h MenuElement.h pugixml.hpp Map.cpp Map.h Tower.h Handler.h Layout.h TowerPriceDisplay.h TowerInterface.h FieldInterface.h Menu.h
	g++ -Wall -std=c++14 -c Map.cpp

PathField.o : PathField.cpp FieldInterface.h PathField.h
	g++ -Wall -std=c++14 -c PathField.cpp

TowerPriceDisplay.o : TowerPriceDisplay.h DisplayInterface.h TowerPriceDisplay.cpp
	g++ -Wall -std=c++14 -c TowerPriceDisplay.cpp

Splash.o : Algorithm.h Splash.h Splash.cpp Handler.h SceneInterface.h
	g++ -Wall -std=c++14 -c Splash.cpp

UpgradeDisplay.o : TowerInterface.h DisplayInterface.h UpgradeDisplay.h UpgradeDisplay.cpp Tower.h
	g++ -Wall -std=c++14 -c UpgradeDisplay.cpp

pugixml.o : pugixml.hpp pugixml.cpp pugiconfig.hpp
	g++ -Wall -std=c++14 -c pugixml.cpp

Bezier.o : Algorithm.h Bezier.h Bezier.cpp
	g++ -Wall -std=c++14 -c Bezier.cpp

Creep.o : FieldInterface.h SimpleField.h SceneInterface.h Algorithm.h Creep.cpp pugixml.hpp Creep.h Tower.h Layout.h TowerInterface.h Bezier.h
	g++ -Wall -std=c++14 -c Creep.cpp

Menu.o : Menu.cpp SceneInterface.h MenuElement.h pugixml.hpp pugiconfig.hpp Menu.h
	g++ -Wall -std=c++14 -c Menu.cpp

MenuElement.o : AudioPlayer.h SceneInterface.h MenuElement.cpp MenuElement.h pugixml.hpp Handler.h Functor.h
	g++ -Wall -std=c++14 -c MenuElement.cpp

Game.o : Timer.h SceneInterface.h Game.h DisplayInterface.h UpgradeDisplay.h AudioPlayer.h MenuElement.h pugixml.hpp Splash.h Menu.h Transitional.h Handler.h TowerPriceDisplay.h Game.cpp Map.h
	g++ -Wall -std=c++14 -c Game.cpp

Wave.o : Wave.h SimpleField.h SceneInterface.h pugixml.hpp Creep.h Tower.h Layout.h TowerInterface.h FieldInterface.h Wave.cpp
	g++ -Wall -std=c++14 -c Wave.cpp

EmptyField.o : FieldInterface.h pugixml.hpp EmptyField.cpp EmptyField.h
	g++ -Wall -std=c++14 -c EmptyField.cpp

Layout.o : Wave.h PathField.h SceneInterface.h FieldInterface.h WaterField.h pugixml.hpp Creep.h Tower.h Layout.h Layout.cpp TowerInterface.h EmptyField.h SimpleField.h
	g++ -Wall -std=c++14 -c Layout.cpp

Tower.o : Wave.h SimpleField.h SceneInterface.h Algorithm.h pugixml.hpp Creep.h Tower.cpp Tower.h TowerInterface.h
	g++ -Wall -std=c++14 -c Tower.cpp

Transitional.o : Transitional.cpp Handler.h Transitional.h SceneInterface.h
	g++ -Wall -std=c++14 -c Transitional.cpp

AudioPlayer.o : pugixml.hpp AudioPlayer.h pugiconfig.hpp AudioPlayer.cpp
	g++ -Wall -std=c++14 -c AudioPlayer.cpp

Handler.o : Handler.cpp Handler.h
	g++ -Wall -std=c++14 -c Handler.cpp

Algorithm.o : Algorithm.h Algorithm.cpp
	g++ -Wall -std=c++14 -c Algorithm.cpp

WaterField.o : WaterField.cpp WaterField.h FieldInterface.h
	g++ -Wall -std=c++14 -c WaterField.cpp

main.o : AudioPlayer.h Game.h Timer.h main.cpp SceneInterface.h
	g++ -Wall -std=c++14 -c main.cpp

clean:
	rm -rf *.o happyRUN

format:
	-astyle --style=kr --unpad-paren --indent=tab --align-reference=name --align-pointer=name *.cpp *.hpp
	-rm -rf *.orig