#include <game_manager/game_manager.hpp>
#include <sf_graphics/sf_window.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <loaders/config_loader.hpp>

int main() {


    sf::RenderWindow window(
    ::sf::VideoMode::getDesktopMode(),
    "MyApp",
            sf::Style::Fullscreen
    );

    window.setFramerateLimit(15);


    game_manager::SfWindow sf_window(window);

    game_manager::imported::ConfigJsonLoader loader;

    game_manager::Config::load(std::filesystem::path(__FILE__).parent_path() / "../config.json", loader);

    game_manager::GameManager manager(sf_window, sf_window);

    manager.open_main_menu();

    manager.run();

    return 0;
}
