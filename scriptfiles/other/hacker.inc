#if defined _hacker_inc
	#endinput
#endif
#define _hacker_inc
#define     NPC_HACKER                              208.7502,-225.6151,1.7786

new HackFlood[MAX_PLAYERS][6];

//public`s
hacker_OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(PRESSED(KEY_WALK) && IsPlayerInRangeOfPoint(playerid,1.5, NPC_HACKER)) return NPC_HackD(playerid);
	return 1;
}
hacker_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	switch(dialogid){
		case D_QUEST_HACKER:{
			if(!response) return 1;
			if(CI[playerid][QuestHacker][listitem]) return SendClientMessage(playerid, COLOR_GREY, "Вы уже выполнили данное задание!");
			if(CI[playerid][QuestHacker][0] == listitem) return ShowQuestHacker(playerid, listitem+1);
			if(!CI[playerid][QuestHacker][listitem-1]) return SendClientMessage(playerid, COLOR_GREY, "Вы не выполнили прошлое задание!");
			return ShowQuestHacker(playerid, listitem+1);
		}
		case D_QUEST_HACKER_1:{
			if(!response) return 1;
			SendClientMessage(playerid, COLOR_GRAY, "[Хакер]: Отлично! Держи оборудование! Надеюсь ты разберешься как оно работает.");
			SetPVarInt(playerid,"HackerQuest1", 1);
			SendClientMessage(playerid, COLOR_GRAY, "[СИСТЕМА]: Найдите любого человека и используйте оборудования (/hacker).");
			return 1;
		}
		case D_QUEST_HACKER_2:{
			if(!response) return 1;
			SendClientMessage(playerid, COLOR_GRAY, "[Хакер]: Вот и отлично! Держи оборудование. (/hacker)");
			SendClientMessage(playerid, COLOR_GRAY, "[Хакер]: Местоположение радиовышки скинул на твой GPS.");
			SetPVarInt(playerid,"HackerQuest2", 1);
			EnableGPSForPlayer(playerid, 1462.8285,-775.3546,92.8073);
		}
		case D_QUEST_HACKER_3:{
			if(!response) return 1;
			SPD(playerid, D_QUEST_CLEAR, DIALOG_STYLE_INPUT, "/hacker",""W"Введите ID игрока которого хотите освободить от "R"розыска"W":",">>>","x");
		}
		case D_QUEST_HACKER_3_1:{
			if(!response) return 1;
			if(!IsAWanteds()) return SendClientMessage(playerid, COLOR_GREY, "[Система]: В розыске пока никого нет. Поробуй взять задание чуть чуть позже.");
			SendClientMessage(playerid, COLOR_GREY, "[Хакер]: Я в тебе не сомневался! Держи оборудование. (/hacker)");
			SendClientMessage(playerid, COLOR_GREY, "[Хакер]: Местоположение я тебе скинул на твой GPS.");
			EnableGPSForPlayer(playerid, 1643.3060,-1681.9083,21.4215);
			SetPVarInt(playerid, "HackerQuest3", 1);
		}
		case D_QUEST_HACKER_4:{
			if(!response) return 1;
			SendClientMessage(playerid, COLOR_GREY, "[Хакер]: Удачного тебе пути. Держи оборудование. (/hacker)");
			SendClientMessage(playerid, COLOR_GREY, "[Хакер]: Местоположение я тебе скинул на твой GPS.");
			SendClientMessage(playerid, COLOR_RED,  "[Мысли]: Мне кажется или он пытается меня развести...");
			EnableGPSForPlayer(playerid, 1395.3621,-1787.1383,13.5469);
			SetPVarInt(playerid, "HackerQuest4", 1);
		}
		case D_QUEST_CLEAR:{
			if(!response) return 1;
			new ID = strval(inputtext);
			if(!IsPlayerConnected(ID)) return SendClientMessage(playerid, COLOR_GRAY, "Игрок не в сети!");
			if(!TI[ID][tLogin]) return SendClientMessage(playerid, COLOR_RED, "Игрок не авторизован на сервере!");
			if(!CI[ID][cWanted]) return SendClientMessage(playerid, COLOR_GREY, "Игрок не в розыске");
			if(CI[ID][cWanted] > 2) return SendClientMessage(playerid, COLOR_GREY, "Вы не можете снимать розыск больше двух звёзд!");
			SetPVarInt(playerid, "WantedID", ID);
			JobTempProcess[playerid] = 31;
			TI[playerid][tProcess][0] = 0;
			TI[playerid][tProcess][1] = 10;
			PlayerTextDrawColor(playerid, YandNsysTDPlayer[playerid][1], -1);
			for(new YN = 0;YN < 3;YN++) {
				TextDrawShowForPlayer(playerid, YandNsysTD[YN]);
				if(YN < 2) PlayerTextDrawShow(playerid,YandNsysTDPlayer[playerid][YN]);
			}
			RandomYareNforJOBS(playerid);

		}
		case D_MENU_HACKER_TEST:{
			if(!response) return 1;
			switch(listitem){
				case 0: if (!GetPVarInt(playerid, "HackerQuest1")) return SendClientMessage(playerid, COLOR_GREY, "Вам не доступно данное действие!"); else return StartHacker(playerid, 1);
				case 1: if (!GetPVarInt(playerid, "HackerQuest2")) return SendClientMessage(playerid, COLOR_GREY, "Вам не доступно данное действие!"); else return StartHacker(playerid, 2);
				case 2: if (!GetPVarInt(playerid, "HackerQuest3")) return SendClientMessage(playerid, COLOR_GREY, "Вам не доступно данное действие!"); else return StartHacker(playerid, 3);
				case 3: if (!GetPVarInt(playerid, "HackerQuest4")) return SendClientMessage(playerid, COLOR_GREY, "Вам не доступно данное действие!"); else return StartHacker(playerid, 4);
			}
			return 1;
		}
		case D_QUEST_HACKER_1_INPUT:{
			if(!response) return 1;
			new ID = strval(inputtext);
			if(ID == playerid) return SendClientMessage(playerid,COLOR_GRAY,"Нельзя указывать свой ID!");
			if(!IsPlayerConnected(ID)) return SendClientMessage(playerid,COLOR_GRAY,"Игрок не в сети");
			if(!TI[ID][tLogin]) return SendClientMessage(playerid, COLOR_RED, "Игрок не авторизован на сервере!");
			new Float:plX, Float:plY, Float:plZ;
			GetPlayerPos(ID, plX, plY, plZ);
			if(!IsPlayerInRangeOfPoint(playerid, 15.0, plX, plY, plZ)) return SendClientMessage(playerid, -1, "Игрок слишком далеко! Вы должны быть с ним в радиусе 15 метров!");
			ShowHackerStats(playerid, ID);
		}
		case D_MENU_HACKER:{
			if(!response) return 1;
			return System32Hacker(playerid, listitem+1);
		}
		case D_MENU_HACKER_ONE:
		{
			if(!response) return 1;
			if(HackFlood[playerid][0] > gettime()) return SendClientMessage(playerid, COLOR_RED, "Данную функцию можно использовать раз в час."); 
			HackFlood[playerid][0] = gettime() + 3600;
			new IpD = strval(inputtext);
			if(!IsPlayerConnected(IpD)) return SendClientMessage(playerid, COLOR_RED, "Игрок не в сети!");
			if(!TI[IpD][tLogin]) return SendClientMessage(playerid, COLOR_RED, "Игрок не авторизован на сервере!");
			if(!CI[IpD][pPhone]) return SendClientMessage(playerid, COLOR_GREY, "У Вас нет телефона");
			new Float:posXX, Float:PosYY, Float:posZZ;
			GetPlayerPos(IpD, posXX, PosYY, posZZ);
			if(!IsPlayerInRangeOfPoint(playerid,20.0,posXX,PosYY, posZZ)) 
				return SendClientMessage(playerid, COLOR_RED, "Вы слишком далеко от игрока. Игрок должен находится в радиусе до 20.0 метров.");
			SetPVarInt(playerid, "PlayerID", IpD);
			ShowButton(playerid, 33);
			return 1;
		}
		case D_MENU_HACKER_TWO:{
			if(!response) return 1;
			if(HackFlood[playerid][1] > gettime()) return SendClientMessage(playerid, COLOR_RED, "Данную функцию можно использовать раз в 10 минут."); 
			HackFlood[playerid][1] = gettime() + 600;
			new IpD = strval(inputtext);
			if(!IsPlayerConnected(IpD)) return SendClientMessage(playerid, COLOR_RED, "Игрок не в сети!");
			if(!TI[IpD][tLogin]) return SendClientMessage(playerid, COLOR_RED, "Игрок не авторизован на сервере!");
			SetPVarInt(playerid, "PlayerID", IpD);
			ShowButton(playerid, 34);
		}
		case D_MENU_HACKER_THREE:{
			if(!response) return 1;
			return ShowButton(playerid, 35);
		}
		case D_MENU_HACKER_THREE_2:{
			if(!response) return 1;
			if(HackFlood[playerid][2] > gettime()) return SendClientMessage(playerid, COLOR_RED, "Данную функцию можно использовать раз в час."); 
			HackFlood[playerid][2] = gettime() + 3600;
			//if(!inputtext) return SendClientMessage(playerid,COLOR_RED,"Вы ничего не написали.");
			new string[150];
			format(string, sizeof(string), "[Неизвестный][%d]: %s",playerid, inputtext);
			SendClientMessageToAll(0xf3E87D6ff, string);
			NextlvlHacker(playerid, 2);
			switch(random(3))
			{
				case 1: {
					CI[playerid][cWanted] = 3;
					UpdateCharacterData(playerid,"pSearch",CI[playerid][cWanted]);
					SetPlayerWantedLevel(playerid, CI[playerid][cWanted]);
					
				}
				default: {

				}
			}

			return 1;
			
			
		}
		case D_MENU_HACKER_FOUR:{
			if(!response) return 1;
			if(HackFlood[playerid][3] > gettime()) return SendClientMessage(playerid, COLOR_RED, "Данную функцию можно использовать раз в час."); 
			HackFlood[playerid][3] = gettime() + 3600;
			new IpD = strval(inputtext);
			if(!IsPlayerConnected(IpD)) return SendClientMessage(playerid, COLOR_RED, "Игрок не в сети!");
			if(!TI[IpD][tLogin]) return SendClientMessage(playerid, COLOR_RED, "Игрок не авторизован на сервере!");
			if(CI[IpD][cJail] == 0 )  return SendClientMessage(playerid, COLOR_RED, "Игрок на свободе!");
	
			SetPVarInt(playerid, "PlayerID", IpD);
			ShowButton(playerid, 36);
		}
		case D_MENU_HACKER_FIVE:{
			if(!response) return 1;
			if(HackFlood[playerid][4] > gettime()) return SendClientMessage(playerid, COLOR_RED, "Данную функцию можно использовать раз в 15 минут."); 
			HackFlood[playerid][4] = gettime() + 900;
			return ShowButton(playerid, 37);
		}
		case D_MENU_HACKER_SIX:{
			return ShowButton(playerid, 38);
		}
		
	}
	return 1;
	
}

// stock`s
stock IsAWanteds()
{
	new num = 0;
	foreach(new i: Player)
	{
		if(CI[i][cWanted] < 3) num++;
	}
	return num;
}
stock DeleteHackerPVar(playerid, idx){
	if(GetPVarInt(playerid, "QuesR")) DeletePVar(playerid, "QuesR");
	switch(idx){
		case 1: if(GetPVarInt(playerid, "HackerQuest1")) DeletePVar(playerid, "HackerQuest1");
		case 2: {
			if(GetPVarInt(playerid, "HackerQuest2")) DeletePVar(playerid, "HackerQuest2");
			if(GetPVarInt(playerid, "HackPosX")){
				DeletePVar(playerid, "HackPosX");
				DeletePVar(playerid, "HackPosY");
				DeletePVar(playerid, "HackPosZ");
			}
			
		}
		case 3: {
				if(GetPVarInt(playerid, "HackerQuest3")) DeletePVar(playerid, "HackerQuest3");
				if(GetPVarInt(playerid, "WantedID")) DeletePVar(playerid, "WantedID");
			}
		case 4: if(GetPVarInt(playerid, "HackerQuest4")) DeletePVar(playerid, "HackerQuest4");
		default:{
			if(GetPVarInt(playerid, "HackerQuest1")) DeletePVar(playerid, "HackerQuest1");
			if(GetPVarInt(playerid, "HackerQuest2")) DeletePVar(playerid, "HackerQuest2");
			if(GetPVarInt(playerid, "HackerQuest3")) DeletePVar(playerid, "HackerQuest3");
			if(GetPVarInt(playerid, "HackerQuest4")) DeletePVar(playerid, "HackerQuest4");
			if(GetPVarInt(playerid, "HackPosX")){
				DeletePVar(playerid, "HackPosX");
				DeletePVar(playerid, "HackPosY");
				DeletePVar(playerid, "HackPosZ");
			}
			if(GetPVarInt(playerid, "WantedID")) DeletePVar(playerid, "WantedID");
		}
	}
	
}
stock ShowHackerStats(playerid, id){
	new string[1250];
	format(string, sizeof(string),
	W"Имя:\t%s\nУровень:\t%i\nПол:\t%s\nСупруг:\t%s\nНомер телефона:\t%i\nМобильный счёт:\t%i\nМашина №1:\t%s (%i)\nМашина №2:\t%s (%i)\nПреступлений:\t%i\nАрестов:\t%i\n\
	Уровень розыска:\t%i",
	CI[id][cName], CI[id][pLevel], CI[id][cSex] ? "Мужчина" : "Женщина", CI[id][pMarried], CI[id][pPhone], CI[id][pMobile],
	gTransport[CarsInfo[id][carModel][0]-400][trName], CarsInfo[id][carModel][0], gTransport[CarsInfo[id][carModel][1]-400][trName], CarsInfo[id][carModel][1],
	CI[id][pCrimes], CI[id][pArrested], CI[id][cWanted]);

	if(CI[id][pMember]) format(string, 128,"%s\nОрганизация:\t\t\t%s", string, FI[CI[id][pMember]][fName]);
	else strcat(string,"\nОрганизация:\t\t\tОтсутствует");
	new house = 0;
	if(CI[id][pHouse] && !CI[id][pRoom]) {
		new classname[15];
		switch(gHouses[CI[id][pHouse]-1][houseClass]) {
		case 0: classname = "Эконом";
		case 1: classname = "Cредний";
		case 2: classname = "Элитный";
		case 3: classname = "Особняк";
		}	
		format(string,128,"%s\n\nЖилье:\t\t\tДом №%d (%s)", string, gHouses[CI[id][pHouse]-1][houseID],classname);
		house = 1;
	}
	if(CI[id][pRoom] && !CI[id][pHouse]) {
		format(string,128,"%s\n\nЖилье:\t\t\tКвартира № %d",string, CI[playerid][pRoom]);
		house = 1;
	}
	if(!house) strcat(string,"\n\nЖилье:\t\t\t\tНет");
	
	if(CI[id][pBusiness]) format(string,128,"%s\nБизнес:\t\t\t%s (%d)",string, gBusiness[CI[id][pBusiness]-1][bizzName],CI[id][pBusiness]);
	else strcat(string,"\nБизнес:\t\t\tОтсутствует");
	SetPVarInt(playerid, "QuesR", 1); 
	SendClientMessage(playerid, COLOR_GREY, "[Система]: Поговорите с Хакером.");
	EnableGPSForPlayer(playerid, NPC_HACKER);
	return SPD(playerid,DIALOG_NONE,DSM, ""P"Статистика",string, "Закрыть", "");
}
stock HackerCamera(playerid, idx)
{
	new Float:X,Float:Y,Float:Z;
	GetPlayerPos(playerid, X,Y,Z);
	SetPVarFloat(playerid, "HackPosX", X);
	SetPVarFloat(playerid, "HackPosY", Y);
	SetPVarFloat(playerid, "HackPosZ", Z);
	switch(idx)
	{
		case 1:{
			SetPlayerCameraPos(playerid, 1541.1815, -1651.5726, 26.5635);
			SetPlayerCameraLookAt(playerid, 1540.6473, -1652.4224, 26.2533);
			SetPlayerPos(playerid,1541.1815, -1651.5726, -4.5635);
			TogglePlayerControllable(playerid, false);
			SetTimerEx("HackCamer",1000*5,false,"i",playerid);
			SendClientMessage(playerid, COLOR_GRAY, "[Мысли]: Отлично, осталось передать информацию Хакеру.");
		}
		case 2:{
			SetPlayerCameraPos(playerid, 1480.5875, -1769.7512, 67.2575);
			SetPlayerCameraLookAt(playerid, 1480.6001, -1768.7527, 66.7675);
			SetPlayerPos(playerid,1480.6001, -1768.7527, 50.7675);
			TogglePlayerControllable(playerid, false);
			CI[playerid][cWanted] = 2;
			UpdateCharacterData(playerid,"pSearch",CI[playerid][cWanted]);
			SetPlayerWantedLevel(playerid, CI[playerid][cWanted]);
			SetTimerEx("HackCamer",1000*5,false,"i",playerid);
			SendClientMessage(playerid, COLOR_GRAY, "[Мысли]: Отлично, я ещё и в розыске...");
		}
	}
	
}
stock StartHacker(playerid, idx) {
	switch(idx) {
		case 1: return SPD(playerid, D_QUEST_HACKER_1_INPUT, DIALOG_STYLE_INPUT,"/hacker",""W"Введите ID игрока о котором хотите узнать информацию",">>>","x");
		case 2: {
			if(!IsPlayerInRangeOfPoint(playerid, 20.0, 1462.8285,-775.3546,92.8073)) return 1;
			JobTempProcess[playerid] = 29;
			TI[playerid][tProcess][0] = 0;
			TI[playerid][tProcess][1] = 10;
			PlayerTextDrawColor(playerid, YandNsysTDPlayer[playerid][1], -1);
			for(new YN = 0;YN < 3;YN++) {
				TextDrawShowForPlayer(playerid, YandNsysTD[YN]);
				if(YN < 2) PlayerTextDrawShow(playerid,YandNsysTDPlayer[playerid][YN]);
			}
			return RandomYareNforJOBS(playerid);
		}
		case 3: {
			if(!IsPlayerInRangeOfPoint(playerid, 15.0, 1643.3060,-1681.9083,21.4215)) return 1;
			JobTempProcess[playerid] = 30;
			TI[playerid][tProcess][0] = 0;
			TI[playerid][tProcess][1] = 10;
			PlayerTextDrawColor(playerid, YandNsysTDPlayer[playerid][1], -1);
			for(new YN = 0;YN < 3;YN++) {
				TextDrawShowForPlayer(playerid, YandNsysTD[YN]);
				if(YN < 2) PlayerTextDrawShow(playerid,YandNsysTDPlayer[playerid][YN]);
			}
			return RandomYareNforJOBS(playerid);
		}
		case 4: {
			new vehicleid = GetPlayerVehicleID(playerid);
			if(FI[VehicleInfo[vehicleid][vTeam]][fType] == fGOVERNMENT) return SendClientMessage(playerid, COLOR_GRAY, "Вы не в транспорте мэрии.");
			JobTempProcess[playerid] = 32;
			TI[playerid][tProcess][0] = 0;
			TI[playerid][tProcess][1] = 10;
			PlayerTextDrawColor(playerid, YandNsysTDPlayer[playerid][1], -1);
			for(new YN = 0;YN < 3;YN++) {
				TextDrawShowForPlayer(playerid, YandNsysTD[YN]);
				if(YN < 2) PlayerTextDrawShow(playerid,YandNsysTDPlayer[playerid][YN]);
			}
			return RandomYareNforJOBS(playerid);
		}
	}
	return 1;
}

stock SaveHacker(playerid, idx = false)
{
	new query[250];
	if(!idx){
		new Hacker[50];
		format(Hacker,sizeof(Hacker),"%i, %i, %i, %i",CI[playerid][QuestHacker][0], CI[playerid][QuestHacker][1], CI[playerid][QuestHacker][2], CI[playerid][QuestHacker][3]);
		mysql_format(connects, query, sizeof(query),"UPDATE `accounts` SET `pQuestHacker`= '%s' WHERE `Name` = '%s' LIMIT 1",Hacker,CI[playerid][cName]);
		mysql_tquery(connects,query);
		query[0] = EOS;

	}
	if(idx){
		mysql_format(connects, query, sizeof(query),"UPDATE `accounts` SET `pHackProg`= '%d' WHERE `Name` = '%s' LIMIT 1",CI[playerid][pHackProg],CI[playerid][cName]);
		mysql_tquery(connects, query);
		query[0] = EOS;
	}
	
	mysql_format(connects, query, sizeof(query),"UPDATE `accounts` SET `pHacker`= '%d' WHERE `Name` = '%s' LIMIT 1",CI[playerid][pHacker],CI[playerid][cName]);
	mysql_tquery(connects, query);
}
stock ShowQuestHacker(playerid, idx){
	switch(idx){
		case 1: return SPD(playerid, D_QUEST_HACKER_1,DIALOG_STYLE_MSGBOX,"Хакер",""W"Привет, я слышал что ты хочешь стать хакером.\n\
		У меня есть к тебе предложение, ты получаешь опыт в сфере хакерства, а я получаю информацию о человеке.\n\
		"R"Мне нельзя светиться, вот я ищу человечка который, сделает это вместо меня.\n"GREEN"Согласен"W"?", ">>>","x");
		case 2: return SPD(playerid, D_QUEST_HACKER_2,DIALOG_STYLE_MSGBOX,"Хакер",""W"Привет, мне вновь нужна твоя помощь.\n\
		Нужно приехать на радиовышку, взломать камеры безопасности.\n\
		После взлома, буду ждать тебя тут.\n\
		"GREEN"Согласен"W"?", ">>>","x");
		case 3: return SPD(playerid, D_QUEST_HACKER_3_1,DIALOG_STYLE_MSGBOX,"Хакер",""W"Привет\n\
		Я тебе скину координаты на GPS, приедишь туда и тебе надо будет взломать Базу Данных ФБР.\n\
		Что-бы проверить взлома Базы Данных, освободи кого нибудь от розыска.\n\
		После взлома буду ждать тебя тут.\n\
		"GREEN"Согласен"W"?", ">>>","x");
		case 4: return SPD(playerid, D_QUEST_HACKER_4, DIALOG_STYLE_MSGBOX, "Хакер", ""W"Привет, в общем мне нужна транспорт мэрии для одного дела.\n\
		"R"Тебе нужно будет приехать к Мэрии нашего города, затем использовать электронную отмычку которую я тебе дам.\n\
		"W"После этого перегнать машину в определённое место, координаты я тебе скину.\n\
		"GREEN"Согласен?",">>>","x");
	}
	return 1;
}
stock ContinueQuest(playerid){
	SendClientMessage(playerid, COLOR_GREY, "Молодец, я в тебе не сомневался!");
	GiveMoney(playerid, 2500);
	if(GetPVarInt(playerid, "HackerQuest1")) CI[playerid][QuestHacker][0] = 1, DeleteHackerPVar(playerid, 1);
	if(GetPVarInt(playerid, "HackerQuest2")) CI[playerid][QuestHacker][1] = 1, DeleteHackerPVar(playerid, 2);
	if(GetPVarInt(playerid, "HackerQuest3")) CI[playerid][QuestHacker][2] = 1, DeleteHackerPVar(playerid, 3);
	if(GetPVarInt(playerid, "HackerQuest4")) CI[playerid][QuestHacker][3] = 1, DeleteHackerPVar(playerid, 4), NextHacker(playerid);
	SaveHacker(playerid, false);
	
	return 1;
}
stock NPC_HackD(playerid){
	if(CI[playerid][QuestHacker][1] == 1 && CI[playerid][QuestHacker][0] == 1 &&
	CI[playerid][QuestHacker][2] == 1 && CI[playerid][QuestHacker][3] == 1) return SendClientMessage(playerid, COLOR_GRAY, "[Хакер]: Извини, но у меня нет для тебя больше задний.");
	if(GetPVarInt(playerid, "QuesR")) return ContinueQuest(playerid);
	if(!IsState(playerid)) return SendClientMessage(playerid,COLOR_GREY,"Ты кто? Иди от сюда! Ты не туда попал.");
	if(CI[playerid][pLevel] < 7) return SendClientMessage(playerid, COLOR_GREY, "У вас маловат lvl. Использовать данный квест можно с 7 lvl");
	if(GetPVarInt(playerid, "HackerQuest1") || GetPVarInt(playerid, "HackerQuest2") || 
	GetPVarInt(playerid, "HackerQuest3") || GetPVarInt(playerid, "HackerQuest4")) return SendClientMessage(playerid, COLOR_GREY, "[Хакер]: Ты ещё тут?.");
	new string[300];
	format(string, sizeof(string), "Название\t\tСтатус\n\
	1. Узнать информацию о личности   \t [ %s"W" ]\n\
	2. Взломать камеры безопасности   \t [ %s"W" ]\n\
	3. Взломать базу данных ФБР       \t [ %s"W" ]\n\
	4. Взломайте и угоните гос. машину\t [ %s"W" ]", 

	CI[playerid][QuestHacker][0] == 0 ? ""R"Не выполнено" : ""GREEN"Выполнено",
	CI[playerid][QuestHacker][1] == 0 ? ""R"Не выполнено" : ""GREEN"Выполнено",
	CI[playerid][QuestHacker][2] == 0 ? ""R"Не выполнено" : ""GREEN"Выполнено",
	CI[playerid][QuestHacker][3] == 0 ? ""R"Не выполнено" : ""GREEN"Выполнено");
	return SPD(playerid, D_QUEST_HACKER, DIALOG_STYLE_TABLIST_HEADERS, "Квестовая лииния", string, ">>>", "x");
}
stock ShowTestHacker(playerid){
	new string[300];
	format(string, sizeof(string), "Название\t\tСтатус\n\
	1. Определение личности        \t [ %s"W" ]\n\
	2. Взлом камеры безопасности   \t [ %s"W" ]\n\
	3. Взлом базы данных ФБР       \t [ %s"W" ]\n\
	4. Взлом гос. машины           \t [ %s"W" ]",
	GetPVarInt(playerid, "HackerQuest1") == 1 ? ""GREEN"Доступно" : ""R"Не доступно",
	GetPVarInt(playerid, "HackerQuest2") == 1 ? ""GREEN"Доступно" : ""R"Не доступно",
	GetPVarInt(playerid, "HackerQuest3") == 1 ? ""GREEN"Доступно" : ""R"Не доступно",
	GetPVarInt(playerid, "HackerQuest4") == 1 ? ""GREEN"Доступно" : ""R"Не доступно");
	SPD(playerid, D_MENU_HACKER_TEST, DIALOG_STYLE_TABLIST_HEADERS, "Меню Хакера", string, ">>>","x");
	return 1;
}
stock NextHacker(playerid){
	CI[playerid][pHacker] = 1;
	UpdateCharacterData(playerid,"pHacker",CI[playerid][pHacker]);
	return 1;
}

forward HackCamer(playerid);
public HackCamer(playerid){
	TogglePlayerControllable(playerid, true);
	SetPlayerPosAC(playerid, GetPVarFloat(playerid, "HackPosX"),GetPVarFloat(playerid, "HackPosY"),GetPVarFloat(playerid, "HackPosZ"),0,0);
	SendClientMessage(playerid,COLOR_GRAY,"[Мысли]: Сейчас бы доехать до хакера без происшетсвий.");
	EnableGPSForPlayer(playerid,NPC_HACKER);
	SetPVarInt(playerid, "QuesR", 1); 
	SetCameraBehindPlayer(playerid);
}
CMD:sethacker(playerid, params[]){
	if(PI[playerid][pAdmin] < 7) return SendClientMessage(playerid, COLOR_RED, "Вам не доступна данная команда");
	extract params -> new id, level;else return SendClientMessage(playerid, COLOR_WHITE,"Используйте: /sethacker [id] [level]");
	if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_GREY, "Игрок не в сети!");
	if(!TI[id][tLogin]) return SendClientMessage(playerid, COLOR_RED, "Игрок не авторизован на сервере!");
	CI[id][pHacker] = level;
	UpdateCharacterData(id, "pHacker", CI[id][pHacker]);
	new string[150];
	format(string, sizeof(string), "Вы успешно выдали игроку %s %d hacker lvl", CI[id][cName], level);
	SendClientMessage(playerid, COLOR_YELLOW, string);
	string[0] = EOS;
	format(string, sizeof(string), "Администратор %s выдал вам %d hacker lvl", CI[playerid][cName], level);
	SendClientMessage(id, COLOR_RED, string);
	if(level == 0)
	{
		CI[id][QuestHacker][0] = 0;
		CI[id][QuestHacker][1] = 0;
		CI[id][QuestHacker][2] = 0;
		CI[id][QuestHacker][3] = 0;
		SaveHacker(id, false);
	}
	else{
		CI[id][QuestHacker][0] = 1;
		CI[id][QuestHacker][1] = 1;
		CI[id][QuestHacker][2] = 1;
		CI[id][QuestHacker][3] = 1;
		SaveHacker(id, false);
	}
	return 1;
}
CMD:hacker(playerid, params[]){
	if(IsAnEnforcement(playerid)){
		extract params -> new id; else return SendClientMessage(playerid, COLOR_WHITE,"Используйте: /hacker [id]");
		if(!IsPlayerConnected(id)) return SendClientMessage(playerid, COLOR_RED, "Игрок не в сети!");
		if(!CI[playerid][pHacker]) return SendClientMessage(playerid, COLOR_RED, "Игрок не хакер!");
		return ShowStatsHacker(playerid, id);
	}
	if(IsState(playerid)) return SendClientMessage(playerid,COLOR_GREY,"Вам не доступна данная команда!");
	if(CI[playerid][pLevel] < 7) return SendClientMessage(playerid, COLOR_GREY, "Данную команду использовать можно с 7 lvl");
	switch(CI[playerid][pHacker]){
		case 0: return ShowTestHacker(playerid);
		default: return ShowMenuHacker(playerid);
	}
	return 1;
}
stock ShowMenuHacker(playerid){
	new string[500];
	format(string, sizeof(string), "Название\t\tСтатус\n\
	1. Взломать телефон            \t [ "GREEN"Доступно"W" ]\n\
	2. Отслеживание игрока\t [ %s"W" ]\n\
	3. Перехватить гос. волну      \t [ %s"W" ]\n\
	4. Выпустить человека из тюрьмы\t [ %s"W" ]\n\
	5. Взломать гос.транспорт      \t [ %s"W" ]\n\
	6. Взломать счёт в банке       \t [ %s"W" ]",
	CI[playerid][pHacker] < 2 ? ""R"Доступно будет с 2 lvl Hacker" : ""GREEN"Доступно",
	CI[playerid][pHacker] < 3 ? ""R"Доступно будет с 3 lvl Hacker" : ""GREEN"Доступно",
	CI[playerid][pHacker] < 4 ? ""R"Доступно будет с 4 lvl Hacker" : ""GREEN"Доступно",
	CI[playerid][pHacker] < 5 ? ""R"Доступно будет с 5 lvl Hacker" : ""GREEN"Доступно",
	CI[playerid][pHacker] < 6 ? ""R"Доступно будет с 6 lvl Hacker" : ""GREEN"Доступно");
	SPD(playerid, D_MENU_HACKER, DIALOG_STYLE_TABLIST_HEADERS, "Меню Хакера", string, ">>>","x");
	return 1;
}
stock System32Hacker(playerid, id){
	switch(id){
		case 1:{
			if(CI[playerid][pHacker] < 1) return SendClientMessage(playerid, COLOR_RED, "Вам не доступна данная функция.");
			SPD(playerid, D_MENU_HACKER_ONE, DSI, "/hacker",""W"Введите ID игрока для взлома телефона.",">>>","x");
		}
		case 2:{
			if(GetPVarInt(playerid, "HackReady")){
				DeletePVar(playerid, "HackReady");
				DeletePVar(playerid, "PlayerID");
				DisablePlayerCheckpoint(playerid);
				return SendClientMessage(playerid, COLOR_RED, "Вы приостоновили поиск человека.");
			}
			if(CI[playerid][pHacker] < 2) return SendClientMessage(playerid, COLOR_RED, "Вам не доступна данная функция.");
			SPD(playerid, D_MENU_HACKER_TWO, DSI, "/hacker",""W"Введите ID игрока для отслеживание в GPS.",">>>","x");
		}
		case 3:{
			if(CI[playerid][pHacker] < 3) return SendClientMessage(playerid, COLOR_RED, "Вам не доступна данная функция.");
			SPD(playerid, D_MENU_HACKER_THREE, DSM, "/hacker",""W"Вы действительно хотите перехватить гос.волну?\n\
			Есть риск что вы будете обьявлены в розыск.",">>>","x");
		}
		case 4:{
			if(CI[playerid][pHacker] < 4) return SendClientMessage(playerid, COLOR_RED, "Вам не доступна данная функция.");
			SPD(playerid, D_MENU_HACKER_FOUR, DSI, "/hacker",""W"Введите ID игрока которого вы хотите выпустить из тюрьмы.",">>>","x");
		}
		case 5:{
			if(CI[playerid][pHacker] < 5) return SendClientMessage(playerid, COLOR_RED, "Вам не доступна данная функция.");
			if(!CI[playerid][pKeyCar]) return SendClientMessage(playerid, COLOR_RED, "У вас нет электронной отмычки!");
			if(!GosCar(GetPlayerVehicleID(playerid))) return SendClientMessage(playerid,COLOR_RED,"Вы не в государственной машине!");
			SPD(playerid, D_MENU_HACKER_FIVE, DSM, "/hacker",""W"Вы действительно хотите использовать электронную отмычку?",">>>","x");
		}
		case 6:{
			if(CI[playerid][pHacker] < 6) return SendClientMessage(playerid, COLOR_RED, "Вам не доступна данная функция.");
			SPD(playerid, D_MENU_HACKER_SIX, DSM, "/hacker",""W"Вы действительно хотите взломать банк?",">>>","x");
		}
	}
	return 1;
}
stock GosCar(vehicleid){
	if(FI[VehicleInfo[vehicleid][vTeam]][fType] == fGOVERNMENT || FI[VehicleInfo[vehicleid][vTeam]][fType] == fENFORCEMENT || FI[VehicleInfo[vehicleid][vTeam]][fType] == fMEDIC) return 1;
	return 0;
}
stock HideButton(playerid, id){
	switch(id){
		case 33:{
			new ID = GetPVarInt(playerid, "PlayerID");
			if(!IsPlayerConnected(ID)) return SendClientMessage(playerid, COLOR_RED, "Игрок вышел из сети!");
			DeletePVar(playerid, "PlayerID");
			NextlvlHacker(playerid, 1);
			InsertPlayerHacker(playerid, "Взлом телефона");
			return GiveMoney(playerid, 5000);

		}
		case 34:{
			new ID = GetPVarInt(playerid, "PlayerID");
			if(!IsPlayerConnected(ID)) return SendClientMessage(playerid, COLOR_RED, "Игрок вышел из сети!");
			SetPVarInt(playerid, "HackReady", 1);
			NextlvlHacker(playerid, 1);
			InsertPlayerHacker(playerid, "Взлом GPS");
			return 1;
		}
		case 35:{
			return SPD(playerid, D_MENU_HACKER_THREE_2, DIALOG_STYLE_INPUT, "/hacker","Введите текст который вы хотите отправить в гос. волну.",">>>","x");
		}
		case 36:{
			new ID = GetPVarInt(playerid, "PlayerID");
			if(!IsPlayerConnected(ID)) return SendClientMessage(playerid, COLOR_RED, "Игрок вышел из сети!");
			NextlvlHacker(playerid, 1);
			unarrest(ID);
			DeletePVar(playerid, "PlayerID");
			InsertPlayerHacker(playerid, "Аннулирование срока игроку");
			return 1;
		}
		case 37:{
			new vehicleid = GetPlayerVehicleID(playerid);
			ToggleEngine(vehicleid, playerid);
			CI[playerid][pKeyCar] --;
			UpdateCharacterData(playerid,"pKeyCar", CI[playerid][pKeyCar]);
			SendClientMessage(playerid, COLOR_GREY, "Вы успешно завели двигатель с помощью электронной отммычки!");
			InsertPlayerHacker(playerid, "Угон государственного транспорта");
			SetPVarInt(playerid, "VehicleHackers", GetPlayerVehicleID(playerid));
			NextlvlHacker(playerid, 1);
		}
		case 38:{
			if(HackFlood[playerid][5] > gettime()) return SendClientMessage(playerid, COLOR_RED, "Данную функцию можно использовать раз в 6 часов."); 
			HackFlood[playerid][5] = gettime() + 21600;
			switch(random(3))
			{
				case 2:{
					CI[playerid][cWanted] = 4;
					UpdateCharacterData(playerid,"pSearch",CI[playerid][cWanted]);
					SetPlayerWantedLevel(playerid, CI[playerid][cWanted]);
					SendClientMessage(playerid, COLOR_RED, "[СИСТЕМА]: Вам было выдано 4 звезды. ");
				}
				default:{ SendClientMessage(playerid, COLOR_RED, "[Мысли]: Слава богу что обошёлся без всяких происшествий."); }
			}
			GiveMoney(playerid, 150000);
			NextlvlHacker(playerid, 1);
			InsertPlayerHacker(playerid, "Ограбление банка");
			return 1;
		}
	}
	return 1;
}
hacker_OnGameModeInit() SetTimer("FindGPS",1000*5,true);

forward FindGPS();
public FindGPS(){
	foreach(new i:Player) {
		if(!GetPVarInt(i, "HackReady")) continue;
		new ID = GetPVarInt(i, "PlayerID");
		if(!IsPlayerConnected(i)){
			DeletePVar(i, "PlayerID");
			break;
		}
		if(!IsPlayerConnected(ID)) {
			DisablePlayerCheckpoint(i);
			DeletePVar(i, "PlayerID");
			SendClientMessage(i, COLOR_RED, "Игрок вышел из игры!");
			break;

		}
		new Float:Xx, Float:Yy, Float:Zz;
		GetPlayerPos(ID, Xx,Yy,Zz);
		EnableGPSForPlayer(i, Xx, Yy, Zz);
	}
	return 1;
}
stock NextlvlHacker(playerid, count){
	CI[playerid][pHackProg]+=count;
	if(CI[playerid][pHackProg] > 19) {
		CI[playerid][pHacker] ++;
		UpdateCharacterData(playerid, "pHacker", CI[playerid][pHacker]);
		CI[playerid][pHackProg] = 0;
	}
	UpdateCharacterData(playerid, "pHackProg", CI[playerid][pHackProg]);
	new string[150];
	format(string, sizeof(string), "До следующего уровня хакера осталось %d/20", CI[playerid][pHackProg]);
	SendClientMessage(playerid, COLOR_YELLOW, string);
	return 1;
}
stock DeletePVarHack(playerid){
	if(GetPVarInt(playerid, "PlayerID")) DeletePVar(playerid, "PlayerID");
	if(GetPVarInt(playerid, "HackReady")) DeletePVar(playerid, "HackReady");
}
stock ShowButton(playerid, id){
	JobTempProcess[playerid] = id;
	TI[playerid][tProcess][0] = 0;
	TI[playerid][tProcess][1] = 10;
	PlayerTextDrawColor(playerid, YandNsysTDPlayer[playerid][1], -1);
	for(new YN = 0;YN < 3;YN++) {
		TextDrawShowForPlayer(playerid, YandNsysTD[YN]);
		if(YN < 2) PlayerTextDrawShow(playerid,YandNsysTDPlayer[playerid][YN]);
	}
	RandomYareNforJOBS(playerid);
	return 1;
}
stock unarrest(playerid){
	CI[playerid][cJail] = 0;
	CI[playerid][cJailTime] = 0;
	UpdateCharacterData(playerid,"cJail",CI[playerid][cJail]);
	UpdateCharacterData(playerid,"cJailTime",CI[playerid][cJailTime]);
	CI[playerid][cWanted] = 0;
	UpdateCharacterData(playerid,"pSearch",CI[playerid][cWanted]);
	SetPlayerWantedLevel(playerid, CI[playerid][cWanted]);
	PlayerSpawn(playerid);
	return 1;
}
stock ShowStatsHacker(playerid, targetid)
{
	new query[156];
	mysql_format(connects, query, sizeof(query),"SELECT * FROM `hacker_stats` WHERE `ID` = '%d'", CI[targetid][cID]);
	mysql_tquery(connects, query, "InfoHacker", "ii", playerid,targetid);
	return 1;
}
CB: InfoHacker(playerid, targetid){
	new rows,ing[1000]; 
	new dates[16], text[64];
	cache_get_row_count(rows);
	if(!rows) {
		Information(playerid, targetid, "Хакер в последнее время ничего не совершал.");
		return 1;
	}
	if(rows)
	{
		if(rows >= 8) {
			new query[128];
			mysql_format(connects, query, sizeof(query),"DELETE FROM `hacker_stats` WHERE `ID` = '%i';",CI[targetid][cID]);
			mysql_query(connects, query);
			for ( new i = 0 ; i < rows ; i ++ )
			{
				cache_get_value_name(i,"text", text,  64);
				cache_get_value_name(i,"date", dates, 16);
				format(ing, sizeof(ing),"%s\t"P"%d. "R"[%s]\t\t\t\t"GREEN"%s\n",ing,i+1,dates,text);
			}
			return 1;
		}
		for ( new i = 0 ; i < rows ; i ++ )
		{
			cache_get_value_name(i,"text", text,  64);
			cache_get_value_name(i,"date", dates, 16);
			format(ing, sizeof(ing),"%s\t"P"%d. "R"[%s]\t\t\t\t"GREEN"%s\n",ing,i+1,dates,text);
		}
	
	}
	Information(playerid, targetid, ing);
	return true;
}
stock Information(playerid, targetid, const text[])
{
	new title[35];
	format(title, sizeof(title), "Досье %s", CI[targetid][cName]);
	new string[1250];
	format(string,sizeof(string),"%s\n"W"Имя:\t\t\t\t\t\t%s\n", string, CI[targetid][cName]);
	format(string,sizeof(string),"%s\n"W"Профессиональность хакера : \t\t%d/6\n", string, CI[targetid][pHacker]);
	format(string,sizeof(string), "%s\n"W"Последние действия хакера:\n\n", string);
	format(string,sizeof(string),"%s\n%s\n\n", string, text);
	SPD(playerid, dNull, DSM, title, string, ">>>","x");
	return 1;
}
stock InsertPlayerHacker(playerid, const text[]){
	MYSQL_GLOBAL[0] = EOS;
	mysql_format(connects, MYSQL_GLOBAL,sizeof(MYSQL_GLOBAL),"INSERT INTO `hacker_stats` (`ID`,`text`,`date`) VALUES ('%d','%s',NOW())",CI[playerid][cID],text);
	mysql_tquery(connects, MYSQL_GLOBAL, "","");
	return 1;
}