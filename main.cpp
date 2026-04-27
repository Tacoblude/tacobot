#include <dpp/dpp.h>
#include <openssl/ssl.h>
#include <string>
const std::string BOT_TOKEN = "token here";
void create_ticket_channel(dpp::cluster& bot, dpp::slashcommand_t& event);
int i = 1;

int main(){
    dpp::cluster bot(BOT_TOKEN);
 
    bot.on_log(dpp::utility::cout_logger());
 
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
    if (event.command.get_command_name() == "about"){event.reply("The tacoserver is owned and created by TacoBlude");}
	if (event.command.get_command_name() == "ping"){event.reply("Online");}
	if (event.command.get_command_name() == "create_ticket"){create_ticket_channel(bot, event);}});

 
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("about", "About Tacoserver", bot.me.id));	
			bot.global_command_create(dpp::slashcommand("ping", "Pings the tacobot", bot.me.id));
			bot.global_command_create(dpp::slashcommand("create_ticket", "creates a ticket", bot.me.id));}});
			bot.start(dpp::st_wait);}

//ticket stuff
void create_ticket_channel(dpp::cluster& bot, dpp::slashcommand_t& event){
dpp::channel ticket;
dpp::snowflake creator = event.command.usr.id; //gets user id of creator of ticket
ticket.set_name("ticket"+std::to_string(i)); //sets name of ticket channel
ticket.set_type(dpp::CHANNEL_TEXT); //sets type to text of ticket channel
ticket.set_guild_id(event.command.guild_id);
bot.channel_create(ticket);i++;
bot.message_create(dpp::message(event.msg->channel_id, creator));}
