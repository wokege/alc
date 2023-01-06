#include <dpp/dpp.h>
#include "string"
#include "locale"

std::locale botLocale("C");

bool is_emote_string(std::string_view s)
{
    // <:a:1>
    auto len = s.length();
    if (len < 6) return false;
    if (s[0] != '<') return false;
    if (s[1] != ':') return false;
    if (s[s.length() - 1] != '>') return false;
    
    auto next = 0;
    for (int i = 2; i < len - 1; ++i)
    {
        auto c = s[i];
        if (c == ':')
        {
            next = i + 1;
            break;
        }
        if (!std::islower(c, botLocale) && !std::isupper(c, botLocale) && !std::isdigit(c) && c != '_') {
            return false;
        }
    }
    
    for (int i = next; i < len - 1; ++i)
    {
        if (!std::isdigit(s[i])) return false;
    }
    
    return true;
}

int main()
{
    auto token = getenv("DISCORD_TOKEN");
    dpp::cluster bot(token);
    bot.intents |= dpp::i_message_content;
    bot.on_log(dpp::utility::cout_logger());
    
    const int32_t target1 = 50;
    std::atomic_int32_t current1 = 0;
    
    const int32_t target2 = 73;
    std::atomic_int32_t current2 = 0;
    
    bot.on_message_create([&current1, &current2](const dpp::message_create_t& event) {
        auto content = std::string_view(event.msg.content);
        if (content.empty()) return;
        if (is_emote_string(content)) return;

        auto bot = event.from->creator;
        if (content == "mẹ thằng alc")
        {
            event.send("memaymem");
        }

        if (content == "alc!uptime")
        {
            auto uptime = bot->uptime();
            event.reply(uptime.to_string());
        }
        
        if (event.msg.author.id == (std::uint64_t) 291569504104742922ULL && event.msg.guild_id == (std::uint64_t) 1027866055856619550)
        {
            current1++;
            current2++;
            
            if (current1 >= target1) {
                event.reply("https://media.discordapp.net/attachments/1030315060737876020/1053190270809812992/alc.png");
                bot->log(dpp::loglevel::ll_info, "dispatched image 1");
                current1 = 0;
            }

            if (current2 >= target2) {
                if (current1 >= 15 && current1 <= (target1 - 8))
                {
                    event.reply("https://media.discordapp.net/attachments/1030315060737876020/1060582175671586866/cac.png");
                    bot->log(dpp::loglevel::ll_info, "dispatched image 2");
                }
                current2 = 0;
            }
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        bot.log(dpp::loglevel::ll_info, "we're ready!");
    });

    bot.start(dpp::st_wait);
}
