#include<SFML/Graphics.hpp>
#include <iostream>

struct WindowOptions {
	int fps = 45;
	int windowWidth = 800;
	int windowHeight = 600;
};

struct CircleOptions {
	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float xScale = 1.0f;
	float yScale = 1.0f;
	float radius = 45.0f;
};

WindowOptions windowOptions;
CircleOptions circleOptions;

/***** GLOBALS *****/
auto antiAlising(int value) {
	sf::ContextSettings settings;
	settings.antialiasingLevel = value;

	return settings;
}

sf::RenderWindow window(
	sf::VideoMode(windowOptions.windowWidth, windowOptions.windowHeight),
	"Hello",
	sf::Style::Default,
	antiAlising(8)
);

/* dinleyici olu�tur */
sf::Event event;

/* daire �ekli olu�tur */
sf::CircleShape circle(circleOptions.radius /* yar��ap */, 85 /* nokta say�s� */);

bool isDraw = false;
/***** END - GLOBALS *****/

void listenCloseEvent() {
	/* e�er window event'i "kapan" ald�ysa: */
	if (event.type == sf::Event::Closed) {
		/* pencereyi kapat */
		window.close();
	}
}

void movementControl(float moveSpeed = 10.0f) {
	/* klavye tu�una bas�ld���nda: */
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::W) circleOptions.yPosition -= moveSpeed;
		if (event.key.code == sf::Keyboard::S) circleOptions.yPosition += moveSpeed;
		if (event.key.code == sf::Keyboard::A) circleOptions.xPosition -= moveSpeed;
		if (event.key.code == sf::Keyboard::D) circleOptions.xPosition += moveSpeed;
	}

	/* klavye tu�undan �ekildi�inde: */
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::W) circle.setOutlineColor(sf::Color::Black);
		if (event.key.code == sf::Keyboard::S) circle.setOutlineColor(sf::Color::White);
		if (event.key.code == sf::Keyboard::D) circle.setOutlineColor(sf::Color::Black);
		if (event.key.code == sf::Keyboard::A) circle.setOutlineColor(sf::Color::White);
	}
}

void sizeControl() {
	/* mouse'a bas�ld���nda: */
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			circleOptions.radius += 10.5f;
		};
		if (event.mouseButton.button == sf::Mouse::Right) {
			circleOptions.radius -= 10.5f;
		};
	}
}

void mouseTracker() {
	std::cout << "Mouse X: " << event.mouseMove.x << std::endl;
	std::cout << "Mouse Y: " << event.mouseMove.y << std::endl;

	/* mouse hareket ettirildi�inde */
	if (event.type == sf::Event::MouseMoved) {
		circleOptions.xPosition = event.mouseMove.x;
		circleOptions.yPosition = event.mouseMove.y;
	}
}

void radiusControl() {
	if (event.type == sf::Event::MouseMoved) {
		float newXPosition = event.mouseMove.x;
		float newYPosition = event.mouseMove.y;

		float radius = abs(circleOptions.xPosition - newXPosition)/2;

		if (isDraw) {
			circleOptions.radius = radius;
		}
	}

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			isDraw = true;
		}
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			isDraw = false;
		}
	}
}

int main() {
	/*
	pencerenin saniyede ka� kare g�sterece�ini belirle
	-- bu �zellik, altta �al��an while d�ng�s�n�n �al��ma h�z�n� girilen de�ere g�re ayarlar. --
	-- �rn: 30 yaz�ld���nda d�ng� saniyede 30 kez �al��acakt�r --
	*/
	window.setFramerateLimit(windowOptions.fps);

	/***** DA�RE �ZELL�KLER� *****/
	/* daireye renk ver */
	circle.setFillColor(sf::Color(37, 219, 49) /* rgba rengi al�r ya da Color::Red gibi verilebilir */);

	/* �er�eve kal�nl���n� belirle */
	circle.setOutlineThickness(5.0f);

	/* �er�eve rengini belirle */
	circle.setOutlineColor(sf::Color::Black);

	/* �er�eve pozisyonunu belirle */
	circle.setPosition(circleOptions.xPosition /* x ekseni */, circleOptions.yPosition /* y ekseni */);
	/***** END - DA�RE �ZELL�KLER� *****/

	/***** PENCERE KONTROL� *****/
	while (window.isOpen()) {
		/***** BA�LATICILAR *****/
		/* circle pozisyonunu ba�lat */
		circle.setPosition(circleOptions.xPosition, circleOptions.yPosition);

		/* circle b�y�kl���n� ba�lat */
		circle.setRadius(circleOptions.radius);
		/***** END - BA�LATICILAR *****/

		/***** PENCERE OLAY D�NLEY�C�LER� *****/
		while (window.pollEvent(event)) {
			/* window'un kapanma �zelli�ini dinler */
			listenCloseEvent();

			/***** KLAVYE VE MOUSE OLAYLARINI D�NLE & YAKALA *****/
			float moveSpeed = 10.0f;

			/* �eklin w,a,s,d tu�lar� ile ilerlemesini sa�lar */
			movementControl(moveSpeed);
			/* mouse 1 ve 2 ile �eklin b�y�y�p k���lmesini sa�lar */
			sizeControl();
			/* �eklin mouse'u takip etmesini sa�lar */
			mouseTracker();

			//radiusControl();
			/***** END - KLAVYE VE MOUSE OLAYLARINI D�NLE & YAKALA *****/
		}
		/***** END - PENCERE OLAY D�NLEY�C�LER� *****/

		/***** EKRAN KONTROL� *****/
		/* arka plan� temizle ve renk ver */
		window.clear(sf::Color::Red);

		/* verilen �ekli �iz */
		window.draw(circle);

		/* yap�lan �izimi g�ster: */
		window.display();
		/***** END - EKRAN KONTROL� *****/
	};
	/***** END - PENCERE KONTROL� *****/

	return 0;
}