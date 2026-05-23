#include <dpp/dpp.h>
#include <openssl/ssl.h>
#include <string>
#include <fstream>
//funtion declearation
void bot();
void clear();
int main(){
    int option;
    std::cout <<"\nOptions\n1. bot\n 2. command clear\n3. exit\n enter an option: ";
    std::cin >>option;
    if(option==1){bot();}
    else if(option==2){clear();}
    else if(option==3){NULL;}
    else{std::cout <<"Not a valid option"; main();}
}

void bot(){
    dpp::cluster bot("!!!!!!ENTER YOUR TOKEN HERE!!!!!!", dpp::i_default_intents | dpp::i_message_content);
    bot.on_log(dpp::utility::cout_logger());
    //make commands do stuff
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "about"){event.reply("The tacoserver is owned and created by TacoBlude");}

        //ban command
        if (event.command.get_command_name() == "ban"){
            dpp::snowflake user_id = std::get<dpp::snowflake>(event.get_parameter("user"));
            bot.guild_ban_add(event.command.guild_id, user_id);
            event.reply("<@"+std::to_string(user_id)+"> was banned by <@"+std::to_string(event.command.usr.id)+"> for "+std::get<std::string>(event.get_parameter("reson")));
            std::fstream fs;
            fs.open ("log.txt", std::fstream::in | std::fstream::out | std::fstream::app);
            fs <<"<@"+std::to_string(user_id)+"> was banned by <@"+std::to_string(event.command.usr.id)+"> for "+std::get<std::string>(event.get_parameter("reson"))+"\n";
            fs.close();}

        //warn command
        if (event.command.get_command_name() == "warn"){
            dpp::snowflake user_id = std::get<dpp::snowflake>(event.get_parameter("user"));
            event.reply("<@"+std::to_string(user_id)+"> was warned for "+std::get<std::string>(event.get_parameter("reson"))+" by <@"+std::to_string(event.command.usr.id)+">");
            std::fstream fs;
            fs.open ("log.txt", std::fstream::in | std::fstream::out | std::fstream::app);
            fs <<"<@"+std::to_string(user_id)+"> was warned for "+std::get<std::string>(event.get_parameter("reson"))+" by <@"+std::to_string(event.command.usr.id)+">\n";
            fs.close();}

        //ping command
        if (event.command.get_command_name() == "ping"){event.reply("Online");}});

    //replyes
    bot.on_message_create([&bot](const dpp::message_create_t& event){
        if (event.msg.content.find("Leonkiller_2 isent a furry") != std::string::npos) {
            event.reply("Thats wrong", true);}});

    //commands
    bot.on_ready([&bot](const dpp::ready_t& event){
        //commands that require perms
        //warn command
        dpp::slashcommand command("warn", "warns a member", bot.me.id);
        command.set_default_permissions(dpp::p_mute_members);
        command.add_option(dpp::command_option(dpp::co_user,"user","user to warn",true));
        command.add_option(dpp::command_option(dpp::co_string,"reson","reson for warning",true));
        bot.global_command_create(command);

        //ban command
        dpp::slashcommand bancommand("ban", "Ban a member", bot.me.id);
        bancommand.set_default_permissions(dpp::p_ban_members);
        bancommand.add_option(dpp::command_option(dpp::co_user,"user","user to ban",true));
        bancommand.add_option(dpp::command_option(dpp::co_string,"reson","reson for ban",true));
        bot.global_command_create(bancommand);

        //user commands
        //about command
        bot.global_command_create(dpp::slashcommand("about","About Tacoserver",bot.me.id));

        //ping command
        bot.global_command_create(dpp::slashcommand("ping","Pings the tacobot",bot.me.id));});

    bot.start(dpp::st_wait);
}
void clear(){
    std::cout <<"not done";
}
