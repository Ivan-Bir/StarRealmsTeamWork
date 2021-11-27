#include <SFML/Graphics.hpp>
#include "include/ClassCard.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
 
using namespace sf;
using namespace std;
 
int main()
{	
	for (int i = 110; i < 156; i++) {
		Card a(i);
		a.GetParameters();
		cout << endl;
		cout << "------------------------------------------";
		cout << endl;
	};
	// // Объект, который, собственно, является главным окном приложения
	// RenderWindow window(VideoMode(1600, 900), "Star Realms");
	// CircleShape shape(200.f);
	// shape.setFillColor(Color::Yellow);
	// // Главный цикл приложения. Выполняется, пока открыто окно
	// while (window.isOpen())
	// {
	// 	// Обрабатываем очередь событий в цикле
	// 	Event event;
	// 	while (window.pollEvent(event))
	// 	{
	// 		// Пользователь нажал на «крестик» и хочет закрыть окно?
	// 		if (event.type == Event::Closed)
	// 			// тогда закрываем его
	// 			window.close();
	// 	}
	// // Отрисовка окна	
	// window.display();
	// }

	// srand(time(NULL));
	// vector<int> v;
	// for (size_t i = 0; i < 14; i ++) {
	// 	v.push_back(i);
	// }
	// random_shuffle(v.begin(), v.end());
	// for (size_t i = 0; i < 14; i ++) {
	// 	cout << v[i] << " ";
	// } 
	return 0;
}