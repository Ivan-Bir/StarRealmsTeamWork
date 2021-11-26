#include <SFML/Graphics.hpp>
 
using namespace sf;
 
int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(1800, 800), "Star Realms");
	CircleShape shape(200.f);
	shape.setFillColor(Color::Yellow);
	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
		}
	// Отрисовка окна	
	window.display();
	}
 
	return 0;
}