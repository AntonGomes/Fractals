#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

sf::VertexArray dragon(sf::VertexArray& x0) {
    // find distance from last point in lines to center of screen
    sf::Vector2f last = x0[x0.getVertexCount() - 1].position;
    sf::Vector2f origin = sf::Vector2f(1280, 800);
    sf::Vector2f diff = last - origin;

    // translate each vertex in lines by diff
    for (unsigned int i = 0; i < x0.getVertexCount(); ++i) {
        sf::Vertex& x0_i = x0[i];
        x0_i.position -= diff;
    }

    // define transform matrix
    sf::Transform transform;
    transform.rotate(90, origin);

    // transform each vertex and append to end
    for (int i = x0.getVertexCount()-2; i>= 0; --i) {
        sf::Vertex& x_i = x0[i];
        std::cout << x_i.position.x << " " << x_i.position.y << std::endl;
        x0.append(sf::Vertex(transform.transformPoint(x_i.position)));
    }
    std::cout << "VERTICES TRANSFORMED" << std::endl;
    std::cout << x0.getVertexCount() << std::endl;
    return x0;
}

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(2560, 1600), "My window");

    // initialise the vertex array
    sf::VertexArray x0(sf::LineStrip);
    x0.append(sf::Vertex(sf::Vector2f(1275.f, 800.f)));
    x0.append(sf::Vertex(sf::Vector2f(1280.f, 800.f)));

    // set iterations
    int n = 20;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
       }

        while (n > 0) {
            sf::VertexArray x1;
            x1 = dragon(x0);

            // display the window
            window.clear();
            window.draw(x1);
            window.display();
            
            x0 = x1;

            sf::sleep(sf::seconds(1));
            n--;
        }
    }
    return 0;
}