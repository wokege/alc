#include <dpp/dpp.h>
#include "string"

int main() {
    auto token = getenv("DISCORD_TOKEN");
    dpp::cluster bot(token);
    bot.intents |= dpp::i_message_content;
    bot.on_log(dpp::utility::cout_logger());
    
    const int32_t target = 50;
    std::atomic_int32_t current = 0;
    bot.on_message_create([&current](const dpp::message_create_t& event) {
        auto bot = event.from->creator;
        if (event.msg.content == "mẹ thằng alc") {
            event.send("memaymem");
        }

        if (event.msg.content == "alc!uptime") {
            auto uptime = bot->uptime();
            event.reply(uptime.to_string());
        }
        
        if (event.msg.author.id == (std::uint64_t) 291569504104742922ULL && event.msg.guild_id == (std::uint64_t) 1027866055856619550) {
            current++;
            if (current >= target) {
                event.reply("https://media.discordapp.net/attachments/1030315060737876020/1053190270809812992/alc.png");
                bot->log(dpp::loglevel::ll_info, "dispatched image");
                current = 0;
            }
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        bot.log(dpp::loglevel::ll_info, "we're ready!");
    });

    bot.start(dpp::st_wait);
}
