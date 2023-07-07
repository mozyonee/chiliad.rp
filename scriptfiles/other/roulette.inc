#if defined _roulette_included
	#endinput
#endif
#define _roulette_included

#define RandomEx%0(%1,%2)		(random(%2-%1)+%1)

#define D_ROULETTE 				12351
#define ROULETTE_OPEN_PRICE		     150

#define MAX_SHOW_PRIZES   30
#define MAX_ROULETTE_PRIZE_LINE	50

#define TABLE_ROULETTE			"roulette_prizes"

#if defined GetName
	#undef GetName
#endif
#define GetName%0(%1) 			player_name[%1]

enum ROULETTE_PE {
	rouletteShowed,
	rouletteStarted,
	rouletteDeals,
	rouletteGUI,

	roulettePrizeID[MAX_SHOW_PRIZES],
	roulettePrizeSlots[MAX_ROULETTE_PRIZE_LINE],
	roulettePrizeNextID,

	rouletteTempID, // pi_id
	rouletteTempArrayID, // pi_array_id
	rouletteTempModelID, // pi_model_id
	rouletteTempTypeID, // pi_type_id
}
new RouletteInfo[MAX_PLAYERS][ROULETTE_PE];

static Text:Roulette_TD[43], PlayerText:Roulette_PTD[MAX_PLAYERS][29];

enum {
	PRIZE_TYPE_MONEY = 1,
	PRIZE_TYPE_DONATE,
	PRIZE_TYPE_EXP,
	PRIZE_TYPE_LEVEL,
	PRIZE_TYPE_BOOST,
	PRIZE_TYPE_VIP_UAHY,
	PRIZE_TYPE_SKIN,
	PRIZE_TYPE_ACCESORY,
}
enum PRIZE_ESING {
	prize_percent_min,
	prize_percent_max,
	prize_TD_name[32],
	prize_text_name[42],
	prize_model_id,
	prize_type_id,
	Float:prize_model_pos[4],
	prize_price,
}

new const PrizeRouletInfo[][PRIZE_ESING] = {
	// Призы | Категория: MAIN  {Мин.%, Макс.%, ...}
	// MONEY
	{0, 30, "MAGNET", "MAGNET", 133, PRIZE_TYPE_ACCESORY, {328.0, 0.0, 0.0, 1.44}},
	{30, 80, "$10000", "$10000", 10000, PRIZE_TYPE_MONEY, {328.0, 0.0, 0.0, 1.44}},
	{80, 90, "$100000", "$100000", 100000, PRIZE_TYPE_MONEY, {328.0, 0.0, 0.0, 1.44}},
	{90, 98, "$500000", "$500000", 500000, PRIZE_TYPE_MONEY, {328.0, 0.0, 0.0, 1.44}},
	{98, 100, "$1000000", "$1000000", 1000000, PRIZE_TYPE_MONEY, {328.0, 0.0, 0.0, 1.44}},
	// DONATE
	{0, 30, "30 UAH", "30 uah", 30, PRIZE_TYPE_DONATE, {270.0, 180.0, 196.0, 2.00}},
	{30, 80, "70 UAH", "70 uah", 70, PRIZE_TYPE_DONATE, {270.0, 180.0, 196.0, 2.00}},
	{80, 90, "150 UAH", "150 uah", 150, PRIZE_TYPE_DONATE, {270.0, 180.0, 196.0, 2.00}},
	{90, 98, "500 UAH", "500 uah", 500, PRIZE_TYPE_DONATE, {270.0, 180.0, 196.0, 2.00}},
	{0, 30, "30 UAH", "30 uah", 30, PRIZE_TYPE_DONATE, {270.0, 180.0, 196.0, 2.00}},
	{30, 80, "70 UAH", "70 uah", 70, PRIZE_TYPE_DONATE, {270.0, 180.0, 196.0, 2.00}},
	{80, 90, "150 UAH", "150 uah", 150, PRIZE_TYPE_DONATE, {270.0, 180.0, 196.0, 2.00}},
	{90, 98, "500 UAH", "500 uah", 500, PRIZE_TYPE_DONATE, {270.0, 180.0, 196.0, 2.00}},
	{98, 100, "1000 UAH", "1000 uah", 1000, PRIZE_TYPE_DONATE, {270.0, 180.0, 196.0, 2.00}},
	//acs
	{90, 98, "DREADLOCKS", "DREADLOCKS", 453, PRIZE_TYPE_ACCESORY, {328.0, 0.0, 0.0, 1.44}},
	{90, 98, "DREADLOCKS", "DREADLOCKS", 453, PRIZE_TYPE_ACCESORY, {328.0, 0.0, 0.0, 1.44}},
	{90, 97, "DREADLOCKS", "DREADLOCKS", 453, PRIZE_TYPE_ACCESORY, {328.0, 0.0, 0.0, 1.44}},
	{90, 98, "DREADLOCKS", "DREADLOCKS", 453, PRIZE_TYPE_ACCESORY, {328.0, 0.0, 0.0, 1.44}},
	{90, 98, "DREADLOCKS", "DREADLOCKS", 453, PRIZE_TYPE_ACCESORY, {328.0, 0.0, 0.0, 1.44}},
	{90, 98, "DREADLOCKS", "DREADLOCKS", 453, PRIZE_TYPE_ACCESORY, {328.0, 0.0, 0.0, 1.44}},
	{98, 100, "KATANA", "KATANA", 461, PRIZE_TYPE_ACCESORY, {328.0, 0.0, 0.0, 1.44}},
	{70, 90, "KATANA", "KATANA", 461, PRIZE_TYPE_ACCESORY, {328.0, 0.0, 0.0, 1.44}},
	{98, 100, "KATANA", "KATANA", 461, PRIZE_TYPE_ACCESORY, {328.0, 0.0, 0.0, 1.44}},
	{70, 90, "KATANA", "KATANA", 461, PRIZE_TYPE_ACCESORY, {328.0, 0.0, 0.0, 1.44}},
	
	// VIP
	{0, 40, "PREMIUM ~y~(1)", "VIP PREMIUM (на 1 доби)", 1, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{40, 70, "VIP PREMIUM ~y~(3)", "PREMIUM (на 3 доби)", 3, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{70, 90, "VIP PREMIUM ~y~(7)", "PREMIUM (на 1 тиждень)", 7, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{90, 97, "VIP PREMIUM ~y~(15)", "PREMIUM (на 2 тижня)", 15, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{97, 100, "VIP PREMIUM ~y~(30)", "PREMIUM (на 1 місяць)", 30, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{0, 40, "PREMIUM ~y~(1)", "VIP PREMIUM (на 1 доби)", 1, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{40, 70, "VIP PREMIUM ~y~(3)", "PREMIUM (на 3 доби)", 3, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{70, 90, "VIP PREMIUM ~y~(7)", "PREMIUM (на 1 тиждень)", 7, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{90, 97, "VIP PREMIUM ~y~(15)", "PREMIUM (на 2 тижня)", 15, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{97, 100, "VIP PREMIUM ~y~(30)", "PREMIUM (на 1 місяць)", 30, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	
	{0, 40, "PREMIUM ~y~(1)", "VIP PREMIUM (на 1 доби)", 1, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{40, 70, "VIP PREMIUM ~y~(3)", "PREMIUM (на 3 доби)", 3, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{70, 90, "VIP PREMIUM ~y~(7)", "PREMIUM (на 1 тиждень)", 7, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{90, 97, "VIP PREMIUM ~y~(15)", "PREMIUM (на 2 тижня)", 15, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	{97, 100, "VIP PREMIUM ~y~(30)", "PREMIUM (на 1 місяць)", 30, PRIZE_TYPE_VIP_UAHY, {270.0, 0.0, 270.0, 1.71}},
	
	{0, 40, "CLOTHER ~y~(177)", "CLOTHER(177)", 177, PRIZE_TYPE_SKIN, {0.0, 0.0, 0.0, 1.0}},
	{40, 70, "CLOTHER ~y~(249)", "CLOTHER(249)", 249, PRIZE_TYPE_SKIN, {0.0, 0.0, 0.0, 1.0}},
	{70, 90, "CLOTHER ~y~(294)", "CLOTHER(294)", 294, PRIZE_TYPE_SKIN, {0.0, 0.0, 0.0, 1.0}},
	{0, 40, "CLOTHER ~y~(177)", "CLOTHER(177)", 177, PRIZE_TYPE_SKIN, {0.0, 0.0, 0.0, 1.0}},
	{40, 70, "CLOTHER ~y~(249)", "CLOTHER(249)", 249, PRIZE_TYPE_SKIN, {0.0, 0.0, 0.0, 1.0}},
	{70, 90, "CLOTHER ~y~(294)", "CLOTHER(294)", 294, PRIZE_TYPE_SKIN, {0.0, 0.0, 0.0, 1.0}},

	// EXP / LVL
	{0, 50, "+1 EXP", "+1 EXP", 1, PRIZE_TYPE_EXP, {169.0, 180.0, 90.0, 1.50}},
	{50, 80, "+2 EXP", "+2 EXP", 2, PRIZE_TYPE_EXP, {169.0, 180.0, 90.0, 1.50}},
	{80, 100, "+5 EXP", "+5 EXP", 5, PRIZE_TYPE_EXP, {169.0, 180.0, 90.0, 1.50}},

	{0, 60, "+1 LEVEL", "+1 LEVEL", 1, PRIZE_TYPE_LEVEL, {169.0, 180.0, 90.0, 1.50}},
	{60, 100, "+2 LEVEL", "+2 LEVEL", 2, PRIZE_TYPE_LEVEL, {169.0, 180.0, 90.0, 1.50}},
	// BOOST
	{0, 30, "X2 ~w~SALARY ~y~(1)", "X2 зарплата (на 1 годину)", 1, PRIZE_TYPE_BOOST, {180.0, 0.0, 270.0, 1.64}},
	{30, 60, "X2 ~w~SALARY ~y~(3)", "X2 зарплата (на 3 години)", 3, PRIZE_TYPE_BOOST, {180.0, 0.0, 270.0, 1.64}},
	{60, 75, "X2 ~w~SALARY ~y~(9)", "X2 зарплата (на 9 годин)", 9, PRIZE_TYPE_BOOST, {180.0, 0.0, 270.0, 1.64}},
	{75, 100, "X2 ~w~SALARY ~y~(24)", "X2 зарплата (на 1 доби)", 24, PRIZE_TYPE_BOOST, {180.0, 0.0, 270.0, 1.64}}
};
#define MAX_ROULETTE_PRIZE	sizeof (PrizeRouletInfo)

stock roulette_NextPrize(playerid) {
	for (new slot_id = 0; slot_id < 5; slot_id++) {
		if (slot_id < 4)
			RouletteInfo[playerid][roulettePrizeSlots][slot_id] = RouletteInfo[playerid][roulettePrizeSlots][slot_id + 1];
		else if (4 == slot_id) 
			RouletteInfo[playerid][roulettePrizeSlots][slot_id] = roulette_GetPrizeID();
		roulette_SetPrizeSlot(playerid, slot_id);
	}
}
stock roulette_UpdateBalanceTD(playerid) {
	new roulette_string[36];
	format(roulette_string, sizeof(roulette_string), "~>~ BALANCE: ~r~~h~~h~~h~%iUAH", CI[playerid][pDonate]);
	PlayerTextDrawSetString(playerid, Roulette_PTD[playerid][10], roulette_string);

	new cases_amount = (CI[playerid][pDonate] / ROULETTE_OPEN_PRICE);
	switch (cases_amount) {
		case 0..9: format(roulette_string, sizeof(roulette_string), "0000000~g~~h~%i", cases_amount);
		case 10..99: format(roulette_string, sizeof(roulette_string), "000000~g~~h~%i", cases_amount);
		default: format(roulette_string, sizeof(roulette_string), "00000~g~~h~%i", cases_amount);
	}
	PlayerTextDrawSetString(playerid, Roulette_PTD[playerid][28], roulette_string);
}
stock roulette_Start(playerid) {
	if (!RouletteInfo[playerid][rouletteShowed] || RouletteInfo[playerid][rouletteStarted])
		return false;
	if (CI[playerid][pDonate] < ROULETTE_OPEN_PRICE) {
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return SendClientMessage(playerid, -1, "Для відкриття необхідно мати "#ROULETTE_OPEN_PRICE" UAH.");
	}
	CI[playerid][pDonate] -= ROULETTE_OPEN_PRICE;
	UpdateCharacterData(playerid, "donatemoney", CI[playerid][pDonate]);

	roulette_UpdateBalanceTD(playerid);
	PlayerTextDrawSetString(playerid, Roulette_PTD[playerid][27], "STARTING..");

	RouletteInfo[playerid][rouletteDeals] = (RandomEx(5, 10) + 35);
	SetTimerEx("roulette_DealTimer", 400, false, "i", playerid);

	return RouletteInfo[playerid][rouletteStarted] = 1;
}
forward roulette_DealTimer(playerid);
public roulette_DealTimer(playerid) {
	if (!IsPlayerConnected(playerid)) 
		return false;
	if (RouletteInfo[playerid][rouletteDeals]) {
		RouletteInfo[playerid][rouletteDeals]--;
		PlayerPlaySound(playerid, 40406, 0.0, 0.0, 0.0);

		SetTimerEx("roulette_DealTimer", (800 - RouletteInfo[playerid][rouletteDeals] * 30), false, "i", playerid);
		roulette_NextPrize(playerid);
	}
	else roulette_Stop(playerid);

	return true;
}
stock roulette_Stop(playerid) {
	if (!IsPlayerConnected(playerid) || !RouletteInfo[playerid][rouletteShowed]) return;
	PlayerTextDrawSetString(playerid, Roulette_PTD[playerid][27], "START");
	PlayerPlaySound(playerid, 31205, 0.0, 0.0, 0.0);

	new
		roulette_string[400],
		player_prize_id = RouletteInfo[playerid][roulettePrizeSlots][2],
		string[128], day, month, year, hour, minute, second;
	getdate(day, month, year);
	gettime(hour, minute, second);
	format(string, sizeof(string), "%0d.%02d.%d | %d:%02d:%02d", day, month, year, hour, minute, second);
	mysql_format(connects, roulette_string, sizeof(roulette_string), "INSERT INTO "TABLE_ROULETTE" (`player_name`, `name`, `model`, `type`, `arrayid`, `date`) VALUES ('%s', '%s', '%i', '%i', '%i', '%s')",
		CI[playerid][cName], PrizeRouletInfo[player_prize_id][prize_text_name], PrizeRouletInfo[player_prize_id][prize_model_id], PrizeRouletInfo[player_prize_id][prize_type_id], player_prize_id, string);
	mysql_tquery(connects, roulette_string);

	roulette_GetPrizesArray(playerid);

	format(roulette_string, sizeof(roulette_string),
		""W"Ви виграли — "P"%s"W". Вітаємо!",

		PrizeRouletInfo[player_prize_id][prize_text_name]
	);
	SPD(playerid, D_ROULETTE, DSM, ""P"Рулетка.", roulette_string, "Закрити", "");

	printf(
		"Гравець %s виграв в рулетці - \"%s\". Поточний баланс: %d",
		CI[playerid][cName], PrizeRouletInfo[player_prize_id][prize_text_name], CI[playerid][pDonate]
	);
	RouletteInfo[playerid][rouletteStarted] = 0;
}
stock roulette_SetPrizeSlot(playerid, prize_id) {
	new
		prize_typeid = RouletteInfo[playerid][roulettePrizeSlots][prize_id],
		prize_model = PrizeRouletInfo[prize_typeid][prize_model_id]
	;
	PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][prize_id], prize_model);
	PlayerTextDrawSetString(playerid, Roulette_PTD[playerid][prize_id + 5], PrizeRouletInfo[prize_typeid][prize_TD_name]);

	switch (PrizeRouletInfo[prize_typeid][prize_type_id]) {
		case PRIZE_TYPE_MONEY: PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][prize_id], 1212);
		case PRIZE_TYPE_DONATE: PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][prize_id], 1874);
		case PRIZE_TYPE_VIP_UAHY: PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][prize_id], 902);
		case PRIZE_TYPE_EXP, PRIZE_TYPE_LEVEL: PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][prize_id], 19134);
		case PRIZE_TYPE_BOOST: PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][prize_id], 1318);
		case PRIZE_TYPE_ACCESORY: PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][prize_id], 18645);
		default: PlayerTextDrawSetPreviewRot(playerid, Roulette_PTD[playerid][prize_id], 0.0, 0.0, 0.0, 100.00);
	}
	PlayerTextDrawSetPreviewRot(playerid, Roulette_PTD[playerid][prize_id], 
		PrizeRouletInfo[prize_typeid][prize_model_pos][0], PrizeRouletInfo[prize_typeid][prize_model_pos][1],
		PrizeRouletInfo[prize_typeid][prize_model_pos][2], PrizeRouletInfo[prize_typeid][prize_model_pos][3]
	);
	PlayerTextDrawSetPreviewVehCol(playerid, Roulette_PTD[playerid][prize_id], 1, 1);

	PlayerTextDrawShow(playerid, Roulette_PTD[playerid][prize_id]);
}
stock roulette_UpdatePrizePTD(playerid) 
	for (new slot_id = 0; slot_id < 5; slot_id++) roulette_SetPrizeSlot(playerid, slot_id);

stock roulette_Show(playerid) {
	if (RouletteInfo[playerid][rouletteShowed]) return false;
	roulette_CreatePTD(playerid);

	roulette_GetPrizesArray(playerid);
	roulette_UpdatePrizePTD(playerid);
	roulette_UpdateBalanceTD(playerid);

	for (new td_id = 0; td_id < sizeof(Roulette_TD); td_id++)
		TextDrawShowForPlayer(playerid, Roulette_TD[td_id]);
	for (new ptd_id = 0; ptd_id < 29; ptd_id++)
		PlayerTextDrawShow(playerid, Roulette_PTD[playerid][ptd_id]);

	RouletteInfo[playerid][rouletteShowed] = 1;
	return SelectTextDraw(playerid, 0xFFFFFF77); 
}
stock roulette_Hide(playerid) {
	if (!RouletteInfo[playerid][rouletteShowed] || RouletteInfo[playerid][rouletteStarted])
		return false;
	for (new td_id = 0; td_id < sizeof(Roulette_TD); td_id++)
		TextDrawHideForPlayer(playerid, Roulette_TD[td_id]);
	for (new ptd_id = 0; ptd_id < 29; ptd_id++)
		PlayerTextDrawHide(playerid, Roulette_PTD[playerid][ptd_id]);
	roulette_DestroyPTD(playerid);

	SPD(playerid, -1, DSM, " ", " ", " ", " ");
	TI[playerid][tDialog] = false;

	RouletteInfo[playerid][rouletteStarted] = RouletteInfo[playerid][rouletteShowed] = 0;

	return CancelSelectTextDraw(playerid);
}
stock roulette_DestroyPTD(playerid) {
	if (!RouletteInfo[playerid][rouletteGUI]) return;
	for (new ptd_id = 0; ptd_id < 29; ptd_id++)
		PlayerTextDrawDestroy(playerid, Roulette_PTD[playerid][ptd_id]);
	RouletteInfo[playerid][rouletteGUI] = 0;
}
stock roulette_CreatePTD(playerid) {
	if (RouletteInfo[playerid][rouletteGUI])
		return false;
	Roulette_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 168.000000, 149.000000, "view_prize_model");
	Roulette_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 225.000000, 149.000000, "view_prize_model");
	Roulette_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 286.000000, 149.000000, "view_prize_model");
	Roulette_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 343.000000, 149.000000, "view_prize_model");
	Roulette_PTD[playerid][4] = CreatePlayerTextDraw(playerid, 402.400085, 149.000000, "view_prize_model");

	for (new td_id = 0; td_id < 5; td_id++) {
		PlayerTextDrawTextSize(playerid, Roulette_PTD[playerid][td_id], 69.000000, 70.000000);
		PlayerTextDrawAlignment(playerid, Roulette_PTD[playerid][td_id], 1);
		PlayerTextDrawColor(playerid, Roulette_PTD[playerid][td_id], -1);
		PlayerTextDrawSetShadow(playerid, Roulette_PTD[playerid][td_id], 0);
		PlayerTextDrawFont(playerid, Roulette_PTD[playerid][td_id], 5);
		PlayerTextDrawSetProportional(playerid, Roulette_PTD[playerid][td_id], 0);
		PlayerTextDrawBackgroundColor(playerid, Roulette_PTD[playerid][td_id], 0);
		PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][td_id], 0);
		PlayerTextDrawSetPreviewRot(playerid, Roulette_PTD[playerid][td_id], 0.000000, 0.000000, 0.000000, 1.000000);
		PlayerTextDrawSetPreviewVehCol(playerid, Roulette_PTD[playerid][td_id], 1, 1);
	}
	Roulette_PTD[playerid][5] = CreatePlayerTextDraw(playerid, 202.500030, 212.500000, "TURISMO");
	Roulette_PTD[playerid][6] = CreatePlayerTextDraw(playerid, 260.399963, 212.500000, "TURISMO");
	Roulette_PTD[playerid][7] = CreatePlayerTextDraw(playerid, 318.999938, 212.500000, "TURISMO");
	Roulette_PTD[playerid][8] = CreatePlayerTextDraw(playerid, 378.000000, 212.500000, "TURISMO");
	Roulette_PTD[playerid][9] = CreatePlayerTextDraw(playerid, 437.699981, 212.500000, "TURISMO");

	for (new ptd_id = 5; ptd_id < 10; ptd_id++) {
		PlayerTextDrawLetterSize(playerid, Roulette_PTD[playerid][ptd_id], 0.154494, 0.736666);
		PlayerTextDrawTextSize(playerid, Roulette_PTD[playerid][ptd_id], 0.000000, 48.000000);
		PlayerTextDrawAlignment(playerid, Roulette_PTD[playerid][ptd_id], 2);
		PlayerTextDrawColor(playerid, Roulette_PTD[playerid][ptd_id], -1);
		PlayerTextDrawUseBox(playerid, Roulette_PTD[playerid][ptd_id], 1);
		PlayerTextDrawBoxColor(playerid, Roulette_PTD[playerid][ptd_id], 168430335);
		PlayerTextDrawSetShadow(playerid, Roulette_PTD[playerid][ptd_id], 0);
		PlayerTextDrawBackgroundColor(playerid, Roulette_PTD[playerid][ptd_id], 255);
		PlayerTextDrawFont(playerid, Roulette_PTD[playerid][ptd_id], 1);
		PlayerTextDrawSetProportional(playerid, Roulette_PTD[playerid][ptd_id], 1);
	}
	Roulette_PTD[playerid][10] = CreatePlayerTextDraw(playerid, 177.948135, 264.333312, "~>~ BALANCE: ~r~~h~~h~~h~0P");
	PlayerTextDrawLetterSize(playerid, Roulette_PTD[playerid][10], 0.184946, 0.882498);
	PlayerTextDrawTextSize(playerid, Roulette_PTD[playerid][10], 636.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, Roulette_PTD[playerid][10], 1);
	PlayerTextDrawColor(playerid, Roulette_PTD[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, Roulette_PTD[playerid][10], 0);
	PlayerTextDrawFont(playerid, Roulette_PTD[playerid][10], 1);
	PlayerTextDrawSetProportional(playerid, Roulette_PTD[playerid][10], 1);

	Roulette_PTD[playerid][11] = CreatePlayerTextDraw(playerid, 179.100067, 293.800048, "view_prizes_list");
	PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][11], 1212);
	PlayerTextDrawSetPreviewRot(playerid, Roulette_PTD[playerid][11], 328.000000, 0.000000, 0.000000, 0.879764);
	Roulette_PTD[playerid][12] = CreatePlayerTextDraw(playerid, 214.200012, 293.800048, "view_prizes_list");
	PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][12], 411);
	PlayerTextDrawSetPreviewRot(playerid, Roulette_PTD[playerid][12], 344.000000, 0.000000, 360.000000, 0.879764);
	PlayerTextDrawSetPreviewVehCol(playerid, Roulette_PTD[playerid][12], 1, 1);
	Roulette_PTD[playerid][13] = CreatePlayerTextDraw(playerid, 249.399963, 293.800048, "view_prizes_list");
	PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][13], 305);
	PlayerTextDrawSetPreviewRot(playerid, Roulette_PTD[playerid][13], 344.000000, 0.000000, 360.000000, 1.048387);
	Roulette_PTD[playerid][14] = CreatePlayerTextDraw(playerid, 285.306549, 293.800048, "view_prizes_list");
	PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][14], 1318);
	PlayerTextDrawSetPreviewRot(playerid, Roulette_PTD[playerid][14], 180.000000, 0.000000, 270.000000, 1.048387);
	Roulette_PTD[playerid][15] = CreatePlayerTextDraw(playerid, 320.908721, 293.800048, "view_prizes_list");
	PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][15], 902);
	PlayerTextDrawSetPreviewRot(playerid, Roulette_PTD[playerid][15], 270.000000, 0.000000, 270.000000, 1.048387);
	Roulette_PTD[playerid][16] = CreatePlayerTextDraw(playerid, 356.510894, 293.800048, "view_prizes_list");
	PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][16], 19134);
	PlayerTextDrawSetPreviewRot(playerid, Roulette_PTD[playerid][16], 169.000000, 180.000000, 90.000000, 1.048387);
	Roulette_PTD[playerid][17] = CreatePlayerTextDraw(playerid, 391.800109, 293.800048, "view_prizes_list");
	PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][17], 1874);
	PlayerTextDrawSetPreviewRot(playerid, Roulette_PTD[playerid][17], 270.000000, 180.000000, 196.000000, 1.326979);
	Roulette_PTD[playerid][18] = CreatePlayerTextDraw(playerid, 427.099822, 293.800048, "view_prizes_list");
	PlayerTextDrawSetPreviewModel(playerid, Roulette_PTD[playerid][18], 18978);
	PlayerTextDrawSetPreviewRot(playerid, Roulette_PTD[playerid][18], 0.000000, 0.000000, 104.000000, 0.909089);

	for (new ptd_id = 11; ptd_id < (11 + 8); ptd_id++) {
		PlayerTextDrawTextSize(playerid, Roulette_PTD[playerid][ptd_id], 33.000000, 29.000000);
		PlayerTextDrawAlignment(playerid, Roulette_PTD[playerid][ptd_id], 1);
		PlayerTextDrawColor(playerid, Roulette_PTD[playerid][ptd_id], -1);
		PlayerTextDrawSetShadow(playerid, Roulette_PTD[playerid][ptd_id], 0);
		PlayerTextDrawBackgroundColor(playerid, Roulette_PTD[playerid][ptd_id], 336860415);
		PlayerTextDrawFont(playerid, Roulette_PTD[playerid][ptd_id], 5);
		PlayerTextDrawSetProportional(playerid, Roulette_PTD[playerid][ptd_id], 0);
		PlayerTextDrawSetSelectable(playerid, Roulette_PTD[playerid][ptd_id], true);
	}
	Roulette_PTD[playerid][19] = CreatePlayerTextDraw(playerid, 195.500213, 314.499908, "~g~MONEY");
	PlayerTextDrawColor(playerid, Roulette_PTD[playerid][19], 8388863);
	Roulette_PTD[playerid][20] = CreatePlayerTextDraw(playerid, 231.002380, 314.499908, "CARS");
	PlayerTextDrawColor(playerid, Roulette_PTD[playerid][20], -65281);
	Roulette_PTD[playerid][21] = CreatePlayerTextDraw(playerid, 266.304534, 314.499908, "SKINS");
	PlayerTextDrawColor(playerid, Roulette_PTD[playerid][21], -8453889);
	Roulette_PTD[playerid][22] = CreatePlayerTextDraw(playerid, 302.406738, 314.499908, "BOOST");
	PlayerTextDrawColor(playerid, Roulette_PTD[playerid][22], -16711681);
	Roulette_PTD[playerid][23] = CreatePlayerTextDraw(playerid, 339.000000, 314.499908, "VIP");
	PlayerTextDrawColor(playerid, Roulette_PTD[playerid][23], -65281);
	Roulette_PTD[playerid][24] = CreatePlayerTextDraw(playerid, 373.411071, 314.499908, "EXP~w~/~R~LVL");
	PlayerTextDrawColor(playerid, Roulette_PTD[playerid][24], -1523963137);
	Roulette_PTD[playerid][25] = CreatePlayerTextDraw(playerid, 408.613220, 314.499908, "DONATE");
	PlayerTextDrawColor(playerid, Roulette_PTD[playerid][25], -5963521);
	Roulette_PTD[playerid][26] = CreatePlayerTextDraw(playerid, 443.715362, 314.499908, "ACCESORY");
	PlayerTextDrawColor(playerid, Roulette_PTD[playerid][26], -2147450625);

	for (new ptd_id = 19; ptd_id < (19 + 8); ptd_id++) {
		PlayerTextDrawLetterSize(playerid, Roulette_PTD[playerid][ptd_id], 0.140184, 0.765833);
		PlayerTextDrawTextSize(playerid, Roulette_PTD[playerid][ptd_id], 0.000000, 46.000000);
		PlayerTextDrawAlignment(playerid, Roulette_PTD[playerid][ptd_id], 2);
		PlayerTextDrawSetShadow(playerid, Roulette_PTD[playerid][ptd_id], 0);
		PlayerTextDrawSetOutline(playerid, Roulette_PTD[playerid][ptd_id], 1);
		PlayerTextDrawBackgroundColor(playerid, Roulette_PTD[playerid][ptd_id], 255);
		PlayerTextDrawFont(playerid, Roulette_PTD[playerid][ptd_id], 2);
		PlayerTextDrawSetProportional(playerid, Roulette_PTD[playerid][ptd_id], 1);
	}
	Roulette_PTD[playerid][27] = CreatePlayerTextDraw(playerid, 320.000000, 244.000793, "START"); // START | STARTING...
	PlayerTextDrawLetterSize(playerid, Roulette_PTD[playerid][27], 0.340496, 1.384166);
	PlayerTextDrawTextSize(playerid, Roulette_PTD[playerid][27], 0.000000, 441.000000);
	PlayerTextDrawAlignment(playerid, Roulette_PTD[playerid][27], 2);
	PlayerTextDrawColor(playerid, Roulette_PTD[playerid][27], 168430335);
	PlayerTextDrawSetShadow(playerid, Roulette_PTD[playerid][27], 0);
	PlayerTextDrawBackgroundColor(playerid, Roulette_PTD[playerid][27], 255);
	PlayerTextDrawFont(playerid, Roulette_PTD[playerid][27], 1);
	PlayerTextDrawSetProportional(playerid, Roulette_PTD[playerid][27], 1);

	Roulette_PTD[playerid][28] = CreatePlayerTextDraw(playerid, 184.000000, 248.800048, "0000000~g~~h~0"); // cases availible count
	PlayerTextDrawLetterSize(playerid, Roulette_PTD[playerid][28], 0.282869, 1.244166);
	PlayerTextDrawTextSize(playerid, Roulette_PTD[playerid][28], 253.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, Roulette_PTD[playerid][28], 1);
	PlayerTextDrawColor(playerid, Roulette_PTD[playerid][28], -1);
	PlayerTextDrawSetShadow(playerid, Roulette_PTD[playerid][28], 0);
	PlayerTextDrawBackgroundColor(playerid, Roulette_PTD[playerid][28], 255);
	PlayerTextDrawFont(playerid, Roulette_PTD[playerid][28], 2);
	PlayerTextDrawSetProportional(playerid, Roulette_PTD[playerid][28], 1);

	return (RouletteInfo[playerid][rouletteGUI] = 1);
}

stock roulette_CreateTD() {
	Roulette_TD[0] = TextDrawCreate(170.000000, 129.333358, "BG_MAIN");
	TextDrawLetterSize(Roulette_TD[0], 0.000000, 22.541496);
	TextDrawTextSize(Roulette_TD[0], 470.000000, 0.000000);
	TextDrawAlignment(Roulette_TD[0], 1);
	TextDrawColor(Roulette_TD[0], 255);
	TextDrawUseBox(Roulette_TD[0], 1);
	TextDrawBoxColor(Roulette_TD[0], 84215295);
	TextDrawSetShadow(Roulette_TD[0], 0);
	TextDrawBackgroundColor(Roulette_TD[0], 255);
	TextDrawFont(Roulette_TD[0], 1);
	TextDrawSetProportional(Roulette_TD[0], 1);

	Roulette_TD[1] = TextDrawCreate(177.000000, 225.197143, "particle:lamp_shad_64");
	TextDrawTextSize(Roulette_TD[1], 293.000000, -97.000000);
	TextDrawAlignment(Roulette_TD[1], 1);
	TextDrawColor(Roulette_TD[1], -1523963308);
	TextDrawSetShadow(Roulette_TD[1], 0);
	TextDrawBackgroundColor(Roulette_TD[1], 0);
	TextDrawFont(Roulette_TD[1], 4);
	TextDrawSetProportional(Roulette_TD[1], 0);

	Roulette_TD[2] = TextDrawCreate(201.000000, 212.801391, "particle:lamp_shad_64");
	TextDrawTextSize(Roulette_TD[2], 239.000000, 120.000000);
	TextDrawAlignment(Roulette_TD[2], 1);
	TextDrawColor(Roulette_TD[2], -1523963351);
	TextDrawSetShadow(Roulette_TD[2], 0);
	TextDrawBackgroundColor(Roulette_TD[2], 0);
	TextDrawFont(Roulette_TD[2], 4);
	TextDrawSetProportional(Roulette_TD[2], 0);

	Roulette_TD[3] = TextDrawCreate(170.000000, 129.333358, "RED_LINE_1");
	TextDrawLetterSize(Roulette_TD[3], 0.000000, -0.188786);
	TextDrawTextSize(Roulette_TD[3], 470.000000, 0.000000);
	TextDrawAlignment(Roulette_TD[3], 1);
	TextDrawColor(Roulette_TD[3], 142);
	TextDrawUseBox(Roulette_TD[3], 1);
	TextDrawBoxColor(Roulette_TD[3], -1523963137);
	TextDrawSetShadow(Roulette_TD[3], 0);
	TextDrawBackgroundColor(Roulette_TD[3], 255);
	TextDrawFont(Roulette_TD[3], 1);
	TextDrawSetProportional(Roulette_TD[3], 1);

	Roulette_TD[4] = TextDrawCreate(319.899993, 132.899932, "~r~~h~~h~~h~Roulette");
	TextDrawLetterSize(Roulette_TD[4], 0.333469, 1.442499);
	TextDrawTextSize(Roulette_TD[4], 0.000000, 300.152099);
	TextDrawAlignment(Roulette_TD[4], 2);
	TextDrawColor(Roulette_TD[4], -2147483419);
	TextDrawUseBox(Roulette_TD[4], 1);
	TextDrawBoxColor(Roulette_TD[4], 44);
	TextDrawSetShadow(Roulette_TD[4], 0);
	TextDrawSetOutline(Roulette_TD[4], 1);
	TextDrawBackgroundColor(Roulette_TD[4], 255);
	TextDrawFont(Roulette_TD[4], 0);
	TextDrawSetProportional(Roulette_TD[4], 1);

	Roulette_TD[5] = TextDrawCreate(174.000000, 155.800048, "BG_BLOCK_PRIZES");
	TextDrawLetterSize(Roulette_TD[5], 0.000000, 7.514704);
	TextDrawTextSize(Roulette_TD[5], 466.000000, 0.000000);
	TextDrawAlignment(Roulette_TD[5], 1);
	TextDrawColor(Roulette_TD[5], -1);
	TextDrawUseBox(Roulette_TD[5], 1);
	TextDrawBoxColor(Roulette_TD[5], 83);
	TextDrawSetShadow(Roulette_TD[5], 0);
	TextDrawBackgroundColor(Roulette_TD[5], 255);
	TextDrawFont(Roulette_TD[5], 1);
	TextDrawSetProportional(Roulette_TD[5], 1);

	Roulette_TD[42] = TextDrawCreate(291.500000, 156.500000, "LD_SPAC:white");
	TextDrawTextSize(Roulette_TD[42], 55.0, 66.7);
	TextDrawAlignment(Roulette_TD[42], 1);
	TextDrawColor(Roulette_TD[42], -1);
	TextDrawSetShadow(Roulette_TD[42], 0);
	TextDrawBackgroundColor(Roulette_TD[42], 255);
	TextDrawFont(Roulette_TD[42], 4);
	TextDrawSetProportional(Roulette_TD[42], 0);

	Roulette_TD[6] = TextDrawCreate(176.500152, 158.500091, "LD_SPAC:white");
	TextDrawColor(Roulette_TD[6], -2079254017);
	Roulette_TD[7] = TextDrawCreate(234.699981, 158.500091, "LD_SPAC:white");
	TextDrawColor(Roulette_TD[7], -2079254017);
	Roulette_TD[8] = TextDrawCreate(293.000000, 158.500091, "LD_SPAC:white");
	TextDrawColor(Roulette_TD[8], -1207952897);
	Roulette_TD[9] = TextDrawCreate(352.000000, 158.500091, "LD_SPAC:white");
	TextDrawColor(Roulette_TD[9], -2079254017);
	Roulette_TD[10] = TextDrawCreate(411.500152, 158.500091, "LD_SPAC:white");
	TextDrawColor(Roulette_TD[10], -2079254017);

	for (new td_id = 6; td_id < (6 + 5); td_id++) {
		TextDrawTextSize(Roulette_TD[td_id], 52.000000, 61.000000);
		TextDrawAlignment(Roulette_TD[td_id], 1);
		TextDrawSetShadow(Roulette_TD[td_id], 0);
		TextDrawBackgroundColor(Roulette_TD[td_id], 255);
		TextDrawFont(Roulette_TD[td_id], 4);
		TextDrawSetProportional(Roulette_TD[td_id], 0);
	}
	Roulette_TD[11] = TextDrawCreate(177.599975, 161.499969, "particle:lamp_shad_64");
	TextDrawColor(Roulette_TD[11], -16777088);
	Roulette_TD[12] = TextDrawCreate(236.000000, 161.499969, "particle:lamp_shad_64");
	TextDrawColor(Roulette_TD[12], -16777088);
	Roulette_TD[13] = TextDrawCreate(295.000000, 161.499969, "particle:lamp_shad_64");
	TextDrawColor(Roulette_TD[13], -2147483393);
	Roulette_TD[14] = TextDrawCreate(353.000000, 161.499969, "particle:lamp_shad_64");
	TextDrawColor(Roulette_TD[14], -16777088);
	Roulette_TD[15] = TextDrawCreate(412.000000, 161.499969, "particle:lamp_shad_64");
	TextDrawColor(Roulette_TD[15], -16777088);

	for (new td_id = 11; td_id < (11 + 5); td_id++) {
		TextDrawTextSize(Roulette_TD[td_id], 51.000000, 57.000000);
		TextDrawAlignment(Roulette_TD[td_id], 1);
		TextDrawSetShadow(Roulette_TD[td_id], 0);
		TextDrawBackgroundColor(Roulette_TD[td_id], 0);
		TextDrawFont(Roulette_TD[td_id], 4);
		TextDrawSetProportional(Roulette_TD[td_id], 0);
	}
	Roulette_TD[16] = TextDrawCreate(297.000000, 228.400024, "LD_BEAT:up");
	TextDrawTextSize(Roulette_TD[16], 47.000000, 12.000000);
	TextDrawAlignment(Roulette_TD[16], 1);
	TextDrawColor(Roulette_TD[16], -1525732810);
	TextDrawSetShadow(Roulette_TD[16], 0);
	TextDrawBackgroundColor(Roulette_TD[16], 255);
	TextDrawFont(Roulette_TD[16], 4);
	TextDrawSetProportional(Roulette_TD[16], 0);

	Roulette_TD[17] = TextDrawCreate(266.000000, 237.400024, "bg_click_start");
	TextDrawTextSize(Roulette_TD[17], 106.000000, 26.000000);
	TextDrawBackgroundColor(Roulette_TD[17], -1523963271);
	Roulette_TD[18] = TextDrawCreate(266.800048, 238.300079, "click_start");
	TextDrawTextSize(Roulette_TD[18], 103.920410, 23.740016);
	TextDrawBackgroundColor(Roulette_TD[18], -483775745);
	TextDrawSetSelectable(Roulette_TD[18], true);

	for (new td_id = 17; td_id < 19; td_id++) {
		TextDrawAlignment(Roulette_TD[td_id], 1);
		TextDrawColor(Roulette_TD[td_id], -1);
		TextDrawSetShadow(Roulette_TD[td_id], 0);
		TextDrawFont(Roulette_TD[td_id], 5);
		TextDrawSetProportional(Roulette_TD[td_id], 0);
		TextDrawSetPreviewModel(Roulette_TD[td_id], 0);
		TextDrawSetPreviewRot(Roulette_TD[td_id], 0.000000, 0.000000, 0.000000, 100.000000);
	}
	Roulette_TD[19] = TextDrawCreate(170.000000, 286.000366, "RED_LINE_2");
	TextDrawLetterSize(Roulette_TD[19], 0.000000, -0.312934);
	TextDrawTextSize(Roulette_TD[19], 470.000000, 0.000000);
	TextDrawAlignment(Roulette_TD[19], 1);
	TextDrawColor(Roulette_TD[19], 89);
	TextDrawUseBox(Roulette_TD[19], 1);
	TextDrawBoxColor(Roulette_TD[19], -466998560);
	TextDrawSetShadow(Roulette_TD[19], 0);
	TextDrawBackgroundColor(Roulette_TD[19], 255);
	TextDrawFont(Roulette_TD[19], 1);
	TextDrawSetProportional(Roulette_TD[19], 1);

	Roulette_TD[20] = TextDrawCreate(371.900115, 264.000000, "~r~~h~~h~~h~"               #ROULETTE_OPEN_PRICE"UAH");
	TextDrawLetterSize(Roulette_TD[20], 0.184946, 0.882498);
	TextDrawTextSize(Roulette_TD[20], 636.000000, 0.000000);
	TextDrawAlignment(Roulette_TD[20], 3);
	TextDrawColor(Roulette_TD[20], -69);
	TextDrawSetShadow(Roulette_TD[20], 0);
	TextDrawBackgroundColor(Roulette_TD[20], 8388863);
	TextDrawFont(Roulette_TD[20], 1);
	TextDrawSetProportional(Roulette_TD[20], 1);

	Roulette_TD[21] = TextDrawCreate(266.000000, 266.499847, "LD_SPAC:white");
	TextDrawTextSize(Roulette_TD[21], 90.000000, 4.659992);
	TextDrawAlignment(Roulette_TD[21], 1);
	TextDrawColor(Roulette_TD[21], -1473631708);
	TextDrawSetShadow(Roulette_TD[21], 0);
	TextDrawBackgroundColor(Roulette_TD[21], 255);
	TextDrawFont(Roulette_TD[21], 4);
	TextDrawSetProportional(Roulette_TD[21], 0);

	Roulette_TD[22] = TextDrawCreate(320.000000, 279.400085, "PRIZES");
	TextDrawLetterSize(Roulette_TD[22], 0.193378, 0.940832);
	TextDrawTextSize(Roulette_TD[22], 0.000000, 72.000000);
	TextDrawAlignment(Roulette_TD[22], 2);
	TextDrawColor(Roulette_TD[22], 255);
	TextDrawSetShadow(Roulette_TD[22], 0);
	TextDrawSetOutline(Roulette_TD[22], 1);
	TextDrawBackgroundColor(Roulette_TD[22], -1037423873);
	TextDrawFont(Roulette_TD[22], 1);
	TextDrawSetProportional(Roulette_TD[22], 1);

	Roulette_TD[23] = TextDrawCreate(174.000000, 296.000000, "bg_prizes");
	TextDrawLetterSize(Roulette_TD[23], 0.000000, 2.737920);
	TextDrawTextSize(Roulette_TD[23], 465.000000, 0.000000);
	TextDrawAlignment(Roulette_TD[23], 1);
	TextDrawColor(Roulette_TD[23], -182);
	TextDrawUseBox(Roulette_TD[23], 1);
	TextDrawBoxColor(Roulette_TD[23], 110);
	TextDrawSetShadow(Roulette_TD[23], 0);
	TextDrawBackgroundColor(Roulette_TD[23], 255);
	TextDrawFont(Roulette_TD[23], 1);
	TextDrawSetProportional(Roulette_TD[23], 1);

	Roulette_TD[24] = TextDrawCreate(172.299896, 294.000000, "click_left_prizes");
	Roulette_TD[25] = TextDrawCreate(462.000061, 294.000061, "click_right_prizes");

	for (new td_id = 24; td_id < 26; td_id++) {
		TextDrawTextSize(Roulette_TD[td_id], 5.000000, 28.629991);
		TextDrawAlignment(Roulette_TD[td_id], 1);
		TextDrawColor(Roulette_TD[td_id], -1);
		TextDrawSetShadow(Roulette_TD[td_id], 0);
		TextDrawBackgroundColor(Roulette_TD[td_id], -1061109728);
		TextDrawFont(Roulette_TD[td_id], 5);
		TextDrawSetProportional(Roulette_TD[td_id], 0);
		TextDrawSetSelectable(Roulette_TD[td_id], true);
		TextDrawSetPreviewModel(Roulette_TD[td_id], 77);
		TextDrawSetPreviewRot(Roulette_TD[td_id], 0.000000, 0.000000, 0.000000, 100.000000);
	}
	Roulette_TD[26] = TextDrawCreate(173.499969, 287.400024, "<");
	TextDrawLetterSize(Roulette_TD[26], 0.153557, 4.341666);
	TextDrawAlignment(Roulette_TD[26], 1);
	TextDrawColor(Roulette_TD[26], 255);
	TextDrawSetShadow(Roulette_TD[26], 0);
	TextDrawBackgroundColor(Roulette_TD[26], 255);
	TextDrawFont(Roulette_TD[26], 3);
	TextDrawSetProportional(Roulette_TD[26], 1);

	Roulette_TD[27] = TextDrawCreate(463.499969, 287.400024, ">");
	TextDrawLetterSize(Roulette_TD[27], 0.153557, 4.341666);
	TextDrawAlignment(Roulette_TD[27], 1);
	TextDrawColor(Roulette_TD[27], 255);
	TextDrawSetShadow(Roulette_TD[27], 0);
	TextDrawBackgroundColor(Roulette_TD[27], 255);
	TextDrawFont(Roulette_TD[27], 3);
	TextDrawSetProportional(Roulette_TD[27], 1);

	Roulette_TD[28] = TextDrawCreate(403.502655, 237.400024, "bg_click_my_prizes");
	TextDrawTextSize(Roulette_TD[28], 60.000000, 26.000000);
	Roulette_TD[29] = TextDrawCreate(404.800903, 238.300079, "click_my_prizes");
	TextDrawTextSize(Roulette_TD[29], 58.000000, 23.740016);

	for (new td_id = 28; td_id < 30; td_id++) {
		TextDrawAlignment(Roulette_TD[td_id], 1);
		TextDrawColor(Roulette_TD[td_id], -1);
		TextDrawSetShadow(Roulette_TD[td_id], 0);
		TextDrawBackgroundColor(Roulette_TD[td_id], -2139094785);
		TextDrawFont(Roulette_TD[td_id], 5);
		TextDrawSetProportional(Roulette_TD[td_id], 0);
		TextDrawSetSelectable(Roulette_TD[td_id], true);
		TextDrawSetPreviewModel(Roulette_TD[td_id], 11);
		TextDrawSetPreviewRot(Roulette_TD[td_id], 0.000000, 0.000000, 0.000000, 100.000000);
	}
	Roulette_TD[30] = TextDrawCreate(479.100250, 124.399978, "X");
	TextDrawLetterSize(Roulette_TD[30], 0.331126, 1.331665);
	TextDrawTextSize(Roulette_TD[30], 10.000000, 10.000000);
	TextDrawAlignment(Roulette_TD[30], 2);
	TextDrawColor(Roulette_TD[30], -1523963137);
	TextDrawSetShadow(Roulette_TD[30], 0);
	TextDrawSetOutline(Roulette_TD[30], 1);
	TextDrawBackgroundColor(Roulette_TD[30], 255);
	TextDrawFont(Roulette_TD[30], 2);
	TextDrawSetProportional(Roulette_TD[30], 1);
	TextDrawSetSelectable(Roulette_TD[30], true);

	Roulette_TD[31] = TextDrawCreate(277.499969, 257.399963, "particle:lamp_shad_64");
	TextDrawTextSize(Roulette_TD[31], 87.000000, -19.000000);
	TextDrawAlignment(Roulette_TD[31], 1);
	TextDrawColor(Roulette_TD[31], -210);
	TextDrawSetShadow(Roulette_TD[31], 0);
	TextDrawBackgroundColor(Roulette_TD[31], 255);
	TextDrawFont(Roulette_TD[31], 4);
	TextDrawSetProportional(Roulette_TD[31], 0);

	Roulette_TD[32] = TextDrawCreate(407.499969, 258.299957, "particle:lamp_shad_64");
	TextDrawTextSize(Roulette_TD[32], 56.000000, -20.000000);
	TextDrawAlignment(Roulette_TD[32], 1);
	TextDrawColor(Roulette_TD[32], -65367);
	TextDrawSetShadow(Roulette_TD[32], 0);
	TextDrawBackgroundColor(Roulette_TD[32], 255);
	TextDrawFont(Roulette_TD[32], 4);
	TextDrawSetProportional(Roulette_TD[32], 0);

	Roulette_TD[33] = TextDrawCreate(416.000000, 242.000000, "MY");
	TextDrawLetterSize(Roulette_TD[33], 0.211180, 0.777499);
	TextDrawTextSize(Roulette_TD[33], 441.000000, 0.000000);
	TextDrawAlignment(Roulette_TD[33], 1);
	TextDrawColor(Roulette_TD[33], 168430335);
	TextDrawSetShadow(Roulette_TD[33], 0);
	TextDrawBackgroundColor(Roulette_TD[33], 255);
	TextDrawFont(Roulette_TD[33], 1);
	TextDrawSetProportional(Roulette_TD[33], 1);

	Roulette_TD[34] = TextDrawCreate(416.000000, 246.200012, "PRIZES");
	TextDrawLetterSize(Roulette_TD[34], 0.340496, 1.384166);
	TextDrawTextSize(Roulette_TD[34], 441.000000, 0.000000);
	TextDrawAlignment(Roulette_TD[34], 1);
	TextDrawColor(Roulette_TD[34], 168430335);
	TextDrawSetShadow(Roulette_TD[34], 0);
	TextDrawBackgroundColor(Roulette_TD[34], 255);
	TextDrawFont(Roulette_TD[34], 1);
	TextDrawSetProportional(Roulette_TD[34], 1);

	Roulette_TD[35] = TextDrawCreate(199.000000, 326.200012, "particle:lamp_shad_64");
	TextDrawTextSize(Roulette_TD[35], 257.000000, -33.000000);
	TextDrawAlignment(Roulette_TD[35], 1);
	TextDrawColor(Roulette_TD[35], -433444304);
	TextDrawSetShadow(Roulette_TD[35], 0);
	TextDrawBackgroundColor(Roulette_TD[35], 255);
	TextDrawFont(Roulette_TD[35], 4);
	TextDrawSetProportional(Roulette_TD[35], 0);

	Roulette_TD[36] = TextDrawCreate(184.000000, 239.800048, "~g~~h~CASES COUNT");
	TextDrawLetterSize(Roulette_TD[36], 0.214934, 1.337499);
	TextDrawTextSize(Roulette_TD[36], 369.000000, 0.000000);
	TextDrawAlignment(Roulette_TD[36], 1);
	TextDrawColor(Roulette_TD[36], 8388863);
	TextDrawSetShadow(Roulette_TD[36], 0);
	TextDrawBackgroundColor(Roulette_TD[36], 255);
	TextDrawFont(Roulette_TD[36], 2);
	TextDrawSetProportional(Roulette_TD[36], 1);

	Roulette_TD[37] = TextDrawCreate(178.299896, 243.500152, "particle:lamp_shad_64");
	TextDrawTextSize(Roulette_TD[37], 76.000000, 20.000000);
	TextDrawAlignment(Roulette_TD[37], 1);
	TextDrawColor(Roulette_TD[37], 8388659);
	TextDrawSetShadow(Roulette_TD[37], 0);
	TextDrawBackgroundColor(Roulette_TD[37], 0);
	TextDrawFont(Roulette_TD[37], 4);
	TextDrawSetProportional(Roulette_TD[37], 0);

	Roulette_TD[38] = TextDrawCreate(176.000000, 257.000000, "particle:lamp_shad_64");
	TextDrawTextSize(Roulette_TD[38], 76.000000, -20.000000);
	TextDrawAlignment(Roulette_TD[38], 1);
	TextDrawColor(Roulette_TD[38], 8388678);
	TextDrawSetShadow(Roulette_TD[38], 0);
	TextDrawBackgroundColor(Roulette_TD[38], 0);
	TextDrawFont(Roulette_TD[38], 4);
	TextDrawSetProportional(Roulette_TD[38], 0);

	Roulette_TD[39] = TextDrawCreate(176.400024, 235.799926, "hud:siterocket");
	TextDrawTextSize(Roulette_TD[39], 13.000000, 13.000000);
	TextDrawAlignment(Roulette_TD[39], 1);
	TextDrawColor(Roulette_TD[39], 1047920895);
	TextDrawSetShadow(Roulette_TD[39], 0);
	TextDrawBackgroundColor(Roulette_TD[39], 255);
	TextDrawFont(Roulette_TD[39], 4);
	TextDrawSetProportional(Roulette_TD[39], 0);

	Roulette_TD[40] = TextDrawCreate(251.300018, 264.800048, "hud:siterocket");
	TextDrawTextSize(Roulette_TD[40], -13.000000, -13.000000);
	TextDrawAlignment(Roulette_TD[40], 1);
	TextDrawColor(Roulette_TD[40], 1047920895);
	TextDrawSetShadow(Roulette_TD[40], 0);
	TextDrawBackgroundColor(Roulette_TD[40], 255);
	TextDrawFont(Roulette_TD[40], 4);
	TextDrawSetProportional(Roulette_TD[40], 0);

	Roulette_TD[41] = TextDrawCreate(170.000000, 336.466796, "RED_LINE_3");
	TextDrawLetterSize(Roulette_TD[41], 0.000000, -0.376194);
	TextDrawTextSize(Roulette_TD[41], 470.000000, 0.000000);
	TextDrawAlignment(Roulette_TD[41], 1);
	TextDrawColor(Roulette_TD[41], 142);
	TextDrawUseBox(Roulette_TD[41], 1);
	TextDrawBoxColor(Roulette_TD[41], -1523963137);
	TextDrawSetShadow(Roulette_TD[41], 0);
	TextDrawBackgroundColor(Roulette_TD[41], 255);
	TextDrawFont(Roulette_TD[41], 1);
	TextDrawSetProportional(Roulette_TD[41], 1);
}
forward roulette_ShowPrizes(playerid);
public roulette_ShowPrizes(playerid) {
	new rows;
	cache_get_row_count(rows);
	if (!rows)
		return SendClientMessage(playerid, -1, "У Вас немає невикористаних призів.");
	new roulette_string[2048];
	for (new i = 0, type_id, model_id, pi_name[32], pi_date[128]; i < rows; i++) {
		cache_get_value_name_int(i, "id", RouletteInfo[playerid][roulettePrizeID][i]);

		cache_get_value_name(i, "name", pi_name, sizeof(pi_name));
		cache_get_value_name(i, "date", pi_date, sizeof(pi_date));

		cache_get_value_name_int(i, "type", type_id);
		cache_get_value_name_int(i, "model", model_id);

		if (0 == i) {
			switch (type_id) {
				case PRIZE_TYPE_SKIN: format(roulette_string, sizeof(roulette_string),
							""P"%d. %s (ID: %d) - (%s)", (i + 1),
							pi_name, model_id, pi_date);
				default:
					format(roulette_string, sizeof(roulette_string), ""G"%d. "W"%s - (%s)", (i + 1),
						pi_name, pi_date
					);
			}
		}
		else {
			switch (type_id) {
				case PRIZE_TYPE_SKIN: format(roulette_string, sizeof(roulette_string),
							"%s\n"P"%d. %s (ID: %d) - (%s)", roulette_string, (i + 1),
							pi_name, model_id, pi_date);
				default: format(roulette_string, sizeof(roulette_string), "%s\n"P"%d. "W"%s - (%s)", roulette_string, (i + 1), pi_name, pi_date);
			}
		}
	}
	SPD(playerid, D_ROULETTE_2, DSL, ""P"Список ваших призів", roulette_string, "Обрати", "Скасувати");

	return true;
}
forward roulette_TakePrize(playerid, prize_bdid);
public roulette_TakePrize(playerid, prize_bdid) {
	new rows;
	cache_get_row_count(rows);
	if (!rows) return;
	new pi_name[32], pi_date[22];

	cache_get_value_name(0, "name", pi_name, sizeof(pi_name));
	cache_get_value_name(0, "date", pi_date, sizeof(pi_date));

	cache_get_value_name_int(0, "id", RouletteInfo[playerid][rouletteTempID]);
	cache_get_value_name_int(0, "arrayid", RouletteInfo[playerid][rouletteTempArrayID]);
	cache_get_value_name_int(0, "model", RouletteInfo[playerid][rouletteTempModelID]);
	cache_get_value_name_int(0, "type", RouletteInfo[playerid][rouletteTempTypeID]);

	new roulette_string[120];
	format(roulette_string, sizeof(roulette_string),
		"{FFFFFF}Найменування: {FF0000}%s\n\
		{FFFFFF}Отримано: {FF0000}%s",
		pi_name, pi_date
	);
	SPD(playerid, D_ROULETTE_3, DSM, ""P"Інформація про приз", roulette_string, "Далі", "Скасувати");
}
stock roulette_SellPrize(playerid, db_id, db_array_id, db_model_id, db_type_id) {
    switch (db_type_id) {
		case PRIZE_TYPE_LEVEL: GiveMoney(playerid, 10000* db_model_id);
		case PRIZE_TYPE_EXP: GiveMoney(playerid, 2500* db_model_id);
		case PRIZE_TYPE_VIP_UAHY:{
			switch(db_model_id){
				case 1:  CI[playerid][pDonate] += 15;
				case 3:  CI[playerid][pDonate] += 45;
				case 7:  CI[playerid][pDonate] += 105;
				case 15: CI[playerid][pDonate] += 225;
				case 30: CI[playerid][pDonate] += 450;
			}
		}
		case PRIZE_TYPE_BOOST:{
		    switch(db_model_id){
				case 1:  CI[playerid][pDonate] += 7;
				case 3:  CI[playerid][pDonate] += 21;
				case 9:  CI[playerid][pDonate] += 63;
				case 24: CI[playerid][pDonate] += 168;
			}
		}
		case PRIZE_TYPE_DONATE: {
			CI[playerid][pDonate] += ((db_model_id/100)*50);
			
		}
		case PRIZE_TYPE_MONEY: GiveMoney(playerid, (db_model_id/100)*50);
		case PRIZE_TYPE_SKIN: {
			switch(db_model_id){
				case 177: GiveMoney(playerid, 150000);
				case 249: GiveMoney(playerid, 450000);
				case 294: GiveMoney(playerid, 6500000);
			}
		}
		case PRIZE_TYPE_ACCESORY:{
			switch(db_model_id){
				case 133: GiveMoney(playerid, 100000);
				case 453: GiveMoney(playerid, 250000);
				case 461: GiveMoney(playerid, 400000);
			}

		}
		default: return true;

	}
	UpdateCharacterData(playerid, "donatemoney", CI[playerid][pDonate]);
    format(CHAT_GLOBAL, sizeof (CHAT_GLOBAL), "{479FF2}[Успіх] "W"Ви успішно продали приз - %s.", PrizeRouletInfo[db_array_id][prize_text_name]);
	SendClientMessage(playerid, COLOR_WHITE, CHAT_GLOBAL), CHAT_GLOBAL[0] = EOS;

	new roulette_string[64];
	mysql_format(connects, roulette_string, sizeof(roulette_string),
		"DELETE FROM "TABLE_ROULETTE" WHERE `id` = %i LIMIT 1", db_id);
	mysql_tquery(connects, roulette_string);

	return true;
}
stock roulette_UsePrize(playerid, db_id, db_array_id, db_model_id, db_type_id) {
	// #pragma unused playerid, db_array_id, db_model_id, db_type_id

	switch (db_type_id) {
		case PRIZE_TYPE_LEVEL: {
			CI[playerid][pLevel] += db_model_id;
			UpdateCharacterData(playerid, "pLevel", CI[playerid][pLevel]);
			CI[playerid][pExp] = 0;

			SendClientMessage(playerid, CGOLD, "Вітаємо! Ваш рівень підвищено.");
		}
		case PRIZE_TYPE_EXP: {
			CI[playerid][pExp] += db_model_id;

			if (CI[playerid][pExp] >= (CI[playerid][pLevel]) * 6) {
				CI[playerid][pLevel] += 1;
				UpdateCharacterData(playerid, "pLevel", CI[playerid][pLevel]);
				CI[playerid][pExp] = 0;
				SendClientMessage(playerid, CGOLD, "Вітаємо! Ваш рівень підвищено.");
			}
		}
		case PRIZE_TYPE_VIP_UAHY:{
		    if(CI[playerid][pPremium] > 1) return SendClientMessage(playerid, COLOR_GREY,"У Вас вже є преміум-акаунт. Рекомендуємо активувати виграних після завершення старого!");
			switch(db_model_id){
				case 1:  CI[playerid][pPremium] = gettime() + 60*60*24;
				case 3:  CI[playerid][pPremium] = gettime() + 60*60*24*3;
				case 7:  CI[playerid][pPremium] = gettime() + 60*60*24*7;
				case 15: CI[playerid][pPremium] = gettime() + 60*60*24*15;
				case 30: CI[playerid][pPremium] = gettime() + 60*60*24*30;
			}
        	UpdateCharacterData(playerid,"Premium",CI[playerid][pPremium]);
		}
		case PRIZE_TYPE_BOOST:{
		    if(CI[playerid][pBoost] > 1) return SendClientMessage(playerid, COLOR_GREY,"У Вас вже є х2 зарплата. Рекомендуємо активувати виграну після завершення старої!");
		    switch(db_model_id){
				case 1:  CI[playerid][pBoost] = gettime() + 60*60*24;
				case 3:  CI[playerid][pBoost] = gettime() + 60*60*24*3;
				case 9:  CI[playerid][pBoost] = gettime() + 60*60*24*9;
				case 24: CI[playerid][pBoost] = gettime() + 60*60*24*24;
			}
            UpdateCharacterData(playerid,"pBoost",CI[playerid][pBoost]);
		}
		case PRIZE_TYPE_DONATE: {
			CI[playerid][pDonate] += db_model_id;
			UpdateCharacterData(playerid, "donatemonegy", CI[playerid][pDonate]);
		}
		case PRIZE_TYPE_MONEY: GiveMoney(playerid, db_model_id);
		case PRIZE_TYPE_SKIN: AddInactiveItem(playerid, 140 + db_model_id, 1);
		case PRIZE_TYPE_ACCESORY: AddInactiveItem(playerid, db_model_id, 1);
		default: return true;
		/* case : {
			// Выдача вип стандарт навсегда
		} */
		
	}
	format(CHAT_GLOBAL, sizeof (CHAT_GLOBAL), "{479FF2}[Успіх] "W"Ви успішно використали приз - %s.", PrizeRouletInfo[db_array_id][prize_text_name]);
	SendClientMessage(playerid, COLOR_WHITE, CHAT_GLOBAL), CHAT_GLOBAL[0] = EOS;

	new roulette_string[64];
	mysql_format(connects, roulette_string, sizeof(roulette_string), 
		"DELETE FROM "TABLE_ROULETTE" WHERE `id` = %i LIMIT 1", db_id);
	mysql_tquery(connects, roulette_string);

	/*format(roulette_string, sizeof(roulette_string), "[DEBUG] PRIZE = %s | AMOUNT = %d", 
		PrizeRouletInfo[db_array_id][prize_text_name], db_model_id
	);
	SendClientMessage(playerid, -1, roulette_string);*/
	return true;
}
stock roulette_GetPrizeID() {
	new prize_id = 0, temp_prizes_array[MAX_ROULETTE_PRIZE_LINE], total_temp_prizes = 0;

	for (new roulette_prizeid = 0; roulette_prizeid < MAX_ROULETTE_PRIZE; roulette_prizeid++) {
		new random_type = RandomEx(PRIZE_TYPE_MONEY, PRIZE_TYPE_BOOST);
		if (PrizeRouletInfo[roulette_prizeid][prize_type_id] != random_type) continue;

		new random_percent = (random(2) + (random(100)) - random(50));
		if (random_percent < 0) random_percent = random(100);

		if (PrizeRouletInfo[roulette_prizeid][prize_percent_min] <= random_percent <= (PrizeRouletInfo[roulette_prizeid][prize_percent_max] + 2)) {
			temp_prizes_array[total_temp_prizes++] = roulette_prizeid;
			if (total_temp_prizes >= sizeof(temp_prizes_array)) break;
		}
	}
	if (total_temp_prizes)
		prize_id = temp_prizes_array[random(total_temp_prizes)];
	else prize_id = random(MAX_ROULETTE_PRIZE);

	return prize_id;
}
stock roulette_GetPrizesArray(playerid) {
	for (new slot_id = 0; slot_id < 5; slot_id++) RouletteInfo[playerid][roulettePrizeSlots][slot_id] = roulette_GetPrizeID();
}
roulette_OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if (!RouletteInfo[playerid][rouletteShowed])
		return false;
	if (_:clickedid == INVALID_TEXT_DRAW) {
		if (RouletteInfo[playerid][rouletteStarted])
			SelectTextDraw(playerid, 0xFFFFFF77);
		else roulette_Hide(playerid);

		return true;
	}
	if (TI[playerid][tDialog])
		return false;
	if (!RouletteInfo[playerid][rouletteStarted]) {
		if (clickedid == Roulette_TD[18]) 
			return roulette_Start(playerid), true;
		if (clickedid == Roulette_TD[29]) {
			RouletteInfo[playerid][rouletteTempID] = RouletteInfo[playerid][rouletteTempArrayID] = 
			RouletteInfo[playerid][rouletteTempModelID] = RouletteInfo[playerid][rouletteTempTypeID] = 0;

			MYSQL_GLOBAL[0] = EOS, mysql_format(connects, MYSQL_GLOBAL, 144, 
				"SELECT * FROM "TABLE_ROULETTE" WHERE `player_name` = '%s' ORDER BY `id` DESC LIMIT "#MAX_SHOW_PRIZES"", 
				CI[playerid][cName]
			);
			mysql_tquery(connects, MYSQL_GLOBAL, "roulette_ShowPrizes", "i", playerid), MYSQL_GLOBAL[0] = EOS;

			return true;
		}
		if (clickedid == Roulette_TD[30]) {
			roulette_Hide(playerid);
			return true;
		}
	}
	return false;
}
