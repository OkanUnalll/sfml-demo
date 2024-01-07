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

/* dinleyici oluþtur */
sf::Event event;

/* daire þekli oluþtur */
sf::CircleShape circle(circleOptions.radius /* yarýçap */, 85 /* nokta sayýsý */);

bool isDraw = false;
/***** END - GLOBALS *****/

void listenCloseEvent() {
	/* eðer window event'i "kapan" aldýysa: */
	if (event.type == sf::Event::Closed) {
		/* pencereyi kapat */
		window.close();
	}
}

void movementControl(float moveSpeed = 10.0f) {
	/* klavye tuþuna basýldýðýnda: */
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::W) circleOptions.yPosition -= moveSpeed;
		if (event.key.code == sf::Keyboard::S) circleOptions.yPosition += moveSpeed;
		if (event.key.code == sf::Keyboard::A) circleOptions.xPosition -= moveSpeed;
		if (event.key.code == sf::Keyboard::D) circleOptions.xPosition += moveSpeed;
	}

	/* klavye tuþundan çekildiðinde: */
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::W) circle.setOutlineColor(sf::Color::Black);
		if (event.key.code == sf::Keyboard::S) circle.setOutlineColor(sf::Color::White);
		if (event.key.code == sf::Keyboard::D) circle.setOutlineColor(sf::Color::Black);
		if (event.key.code == sf::Keyboard::A) circle.setOutlineColor(sf::Color::White);
	}
}

void sizeControl() {
	/* mouse'a basýldýðýnda: */
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

	/* mouse hareket ettirildiðinde */
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
	pencerenin saniyede kaç kare göstereceðini belirle
	-- bu özellik, altta çalýþan while döngüsünün çalýþma hýzýný girilen deðere göre ayarlar. --
	-- örn: 30 yazýldýðýnda döngü saniyede 30 kez çalýþacaktýr --
	*/
	window.setFramerateLimit(windowOptions.fps);

	/***** DAÝRE ÖZELLÝKLERÝ *****/
	/* daireye renk ver */
	circle.setFillColor(sf::Color(37, 219, 49) /* rgba rengi alýr ya da Color::Red gibi verilebilir */);

	/* çerçeve kalýnlýðýný belirle */
	circle.setOutlineThickness(5.0f);

	/* çerçeve rengini belirle */
	circle.setOutlineColor(sf::Color::Black);

	/* çerçeve pozisyonunu belirle */
	circle.setPosition(circleOptions.xPosition /* x ekseni */, circleOptions.yPosition /* y ekseni */);
	/***** END - DAÝRE ÖZELLÝKLERÝ *****/

	/***** PENCERE KONTROLÜ *****/
	while (window.isOpen()) {
		/***** BAÞLATICILAR *****/
		/* circle pozisyonunu baþlat */
		circle.setPosition(circleOptions.xPosition, circleOptions.yPosition);

		/* circle büyüklüðünü baþlat */
		circle.setRadius(circleOptions.radius);
		/***** END - BAÞLATICILAR *****/

		/***** PENCERE OLAY DÝNLEYÝCÝLERÝ *****/
		while (window.pollEvent(event)) {
			/* window'un kapanma özelliðini dinler */
			listenCloseEvent();

			/***** KLAVYE VE MOUSE OLAYLARINI DÝNLE & YAKALA *****/
			float moveSpeed = 10.0f;

			/* þeklin w,a,s,d tuþlarý ile ilerlemesini saðlar */
			movementControl(moveSpeed);
			/* mouse 1 ve 2 ile þeklin büyüyüp küçülmesini saðlar */
			sizeControl();
			/* þeklin mouse'u takip etmesini saðlar */
			mouseTracker();

			//radiusControl();
			/***** END - KLAVYE VE MOUSE OLAYLARINI DÝNLE & YAKALA *****/
		}
		/***** END - PENCERE OLAY DÝNLEYÝCÝLERÝ *****/

		/***** EKRAN KONTROLÜ *****/
		/* arka planý temizle ve renk ver */
		window.clear(sf::Color::Red);

		/* verilen þekli çiz */
		window.draw(circle);

		/* yapýlan çizimi göster: */
		window.display();
		/***** END - EKRAN KONTROLÜ *****/
	};
	/***** END - PENCERE KONTROLÜ *****/

	return 0;
}