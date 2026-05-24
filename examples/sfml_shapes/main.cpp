#include <SFML/Graphics.hpp>
#include <vector>

auto create_shapes() {

  std::vector<sf::Shape*> shapes;

  // circle è di tipo unique_pointer<sf::CircleShape>
  auto circle = std::make_unique<sf::CircleShape>(100.f);
  circle->setFillColor(sf::Color::Green);
  // un unique_pointer non è copiabile, uso std::move
  shapes.push_back(std::move(circle));

  auto rectangle = std::make_unique<sf::CircleShape>(sf::Vector2f{50.f, 200.f});
  rectangle->setFillColor(sf::Color::Blue);
  rectangle->setPosition(sf::Vector2f{450.f, 250.f});
  shapes.push_back(std::move(rectangle));

  return shapes;
}

int main() {
  sf::RenderWindow window{sf::VideoMode(600, 800), "SFML shapes"};
  window.setFramerateLimit(60);  // 60 FPS

  std::vector<std::unique_pointer<sf::Shape>> shapes = create_shapes();

  while (window.isOpen()) {
    // gestisci gli eventi (movimenti o click del mouse, uso della tastiera,
    // ecc.) avvenuti dal frame precedente
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    // aggiorna gli elementi della scena
    for (auto& s : shapes) {
      s->setPosition(s->getPosition() + sf::Vector2f{5.f, 5.f});
    }

    // ridisegna la scena a partire da una finestra ripulita
    window.clear();
    for (auto& s : shapes) {
      window.draw(*s);
    }

    // visualizza la finestra aggiornata
    window.display();
  }

  // il distruttore di shapes distrugge gli unique_pointer
}
