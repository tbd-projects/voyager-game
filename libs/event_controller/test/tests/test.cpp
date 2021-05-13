//
// Created by volodya on 09.05.2021.
//

#include <gtest/gtest.h>

#include "event_controller/event.h"
#include <event_controller/event/fps_event.h>
#include <event_controller/event/keyboard_event.h>
#include "event_controller/i_eventable.h"
#include "event_controller/i_subscriber.h"
#include "event_controller/controller.h"
#include <game_manager/game_manager.hpp>
#include <game_manager/commands/nothing_command.hpp>
#include <event_controller/event/close_event.h>


class TestEventable : public event_controller::IEventable {
    int i = 0;

    std::unique_ptr<event_controller::Event> get_event() override {
        i++;
        switch (i) {
            case 1:
                return std::make_unique<event_controller::FPSEvent>();
                break;
            case 2:
                return std::make_unique<event_controller::KeyboardEvent>(event_controller::Key::Down);
                break;
            default:
                return std::make_unique<event_controller::CloseEvent>();
                break;
        }
    }
};

class TestSubscriber : public event_controller::ISubscriber {
private:
    event_controller::Controller &_controller;
public:
    int i = 0;

    explicit TestSubscriber(event_controller::Controller &controller) : _controller(controller) {}

    std::shared_ptr<event_controller::ICommand> update(event_controller::Event &e) override {
        i++;
        switch (i) {
            case 1:
                EXPECT_EQ(e.type, event_controller::EventType::fps);
                break;
            case 2:
                EXPECT_EQ(e.type, event_controller::EventType::keyboard);
                EXPECT_EQ(
                        dynamic_cast<event_controller::KeyboardEvent &>(e).key,
                        event_controller::Key::Down
                );
                break;
            case 3:
                EXPECT_EQ(e.type, event_controller::EventType::close);
                _controller.stop();
                break;
            default:
                EXPECT_EQ(1, 0); // @todo find correct version
                break;
        }
        return std::make_shared<game_manager::command::DoNothing>();
    };
};

class TestCanvas : public graphics::ICanvas {
public:
    ~TestCanvas() override = default;

    int get_width() override {
        return 0;
    }

    int get_height() override {
        return 0;
    }

    void clear() override {

    }

    void apply() override {

    }
};

TEST(event_controller_tests, controller_constructor) {
    auto eventable = TestEventable();
    auto canvas = TestCanvas();

    auto gm = game_manager::GameManager(canvas, eventable);
    auto controller = event_controller::Controller(gm, eventable);

    TestSubscriber subscriber(controller);

    controller.subscribe(event_controller::EventType::fps, subscriber);
    controller.subscribe(event_controller::EventType::keyboard, subscriber);
    controller.subscribe(event_controller::EventType::close, subscriber);

    controller.run();

    controller.unsubscribe(event_controller::EventType::fps, subscriber);
    controller.unsubscribe(event_controller::EventType::keyboard, subscriber);
    controller.unsubscribe(event_controller::EventType::close, subscriber);


    ASSERT_EQ(subscriber.i, 3);
}