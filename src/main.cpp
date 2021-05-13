#include <game_manager/game_manager.hpp>
#include <game_manager/commands.hpp>
#include <sf_graphics/sf_window.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <loaders/config_loader.hpp>
#include <loaders/init_configs_loaders.hpp>
#include <iostream>


int main() {


    sf::RenderWindow window(
    ::sf::VideoMode::getDesktopMode(),
    "MyApp",
            sf::Style::Fullscreen
    );

    window.setFramerateLimit(60);


    game_manager::SfWindow sf_window(window);

    game_manager::imported::ConfigJsonLoader loader;
    game_manager::imported::InitLoadersForConfig initer;

    game_manager::Config::load(std::filesystem::path(__FILE__).parent_path() / "../config.json", loader, initer);

    game_manager::GameManager manager(sf_window, sf_window);

    game_manager::command::RunMainMenu main_menu;

    main_menu.execute(manager);

    manager.run();

    return 0;
}
