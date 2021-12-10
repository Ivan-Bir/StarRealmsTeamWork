#include <SFML/Graphics.hpp>
#include "project/data/ClassCard.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
 
using namespace sf;
using namespace std;
 
int main()
{	
	
	// // Объект, который, собственно, является главным окном приложения
	 RenderWindow window(VideoMode(1600, 900), "Star Realms");
	Texture texture;
	texture.loadFromFile("./project/include/images/111.jpg");
	Sprite sprite(texture);
	vector<Vector2f> sh;
	double xst=0;
	double yst=0;
	for (int i=0;i<=100;i++){
		sh.push_back(Vector2f(5*i+2.2f,i+2.2f));

	}
	int pos=-1;
	 // Главный цикл приложения. Выполняется, пока открыто окно
	 while (window.isOpen())
	 {
		 window.clear();
	 	// Обрабатываем очередь событий в цикле
	 	Event event;
		pos++;
		if (pos==sh.size()){
			pos=0;
		}
		sprite.setPosition(sh[pos]);
		sprite.scale(1.0001,1.0001);
	 	while (window.pollEvent(event))
	 	{
	 		// Пользователь нажал на «крестик» и хочет закрыть окно?
	 		if (event.type == Event::Closed)
	 			// тогда закрываем его
	 			window.close();
	 	}
	 // Отрисовка окна	
	 window.draw(sprite);
	 window.display();
	 }

	 srand(time(NULL));
	 vector<int> v;
	 for (size_t i = 0; i < 14; i ++) {
	 	v.push_back(i);
	 }
	 random_shuffle(v.begin(), v.end());
	 for (size_t i = 0; i < 14; i ++) {
	 	cout << v[i] << " ";
	 }
	 Card card();
	 cout<< card.

	return 0;
}