//#include <tgbot/tgbot.h>
//
//int main() {
//    setlocale(LC_ALL, "rus");
//
//    TgBot::Bot bot("7715954427:AAH5_r9fch8E_oh1ZoBczw2LLomuFcn6T4Y");
//
//    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
//        if (StringTools::startsWith(message->text, "/start")) {
//            bot.getApi().sendMessage(message->chat->id, "Hello");
//        }
//        else {
//            bot.getApi().sendMessage(message->chat->id, message->text);
//        }
//        });
//
//    try {
//        printf("Бот запущен. Нажмите Ctrl+C для выхода.\n");
//        bot.getApi().deleteWebhook();
//        TgBot::TgLongPoll longPoll(bot);
//        while (true) {
//            longPoll.start();
//        }
//    }
//    catch (std::exception& e) {
//        printf("Ошибка: %s\n", e.what());
//    }
//
//    return 0;
//}

#include <tgbot/tgbot.h>
#include <iostream>
#include <vector>

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    TgBot::Bot bot("7715954427:AAH5_r9fch8E_oh1ZoBczw2LLomuFcn6T4Y");

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        std::vector<TgBot::InlineKeyboardButton::Ptr> row;

        TgBot::InlineKeyboardButton::Ptr myButton1(new TgBot::InlineKeyboardButton);
        myButton1->text = "Button1";
        myButton1->callbackData = "Button1";
        row.push_back(myButton1);

        TgBot::InlineKeyboardButton::Ptr eurButton(new TgBot::InlineKeyboardButton);
        eurButton->text = "EUR";
        eurButton->callbackData = "EUR";
        row.push_back(eurButton);

        TgBot::InlineKeyboardButton::Ptr linkButton(new TgBot::InlineKeyboardButton);
        linkButton->text = "Open Link";
        linkButton->url = "https://www.google.com";
        row.push_back(linkButton);

        keyboard->inlineKeyboard.push_back(row);

        bot.getApi().sendMessage(message->chat->id, "Who? ", false, 0, keyboard);
        });

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "You say: " + message->text);
        });

    try {
        std::cout << "Имя бота: " << bot.getApi().getMe()->username.c_str() << std::endl;
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            std::cout << "Начался лонгпуллинг" << std::endl;
            longPoll.start();
        }
    }
    catch (TgBot::TgException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
