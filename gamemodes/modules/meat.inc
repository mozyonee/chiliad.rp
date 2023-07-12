
enum MeatData {
	Float:minWeight,
	Float:maxWeight,
	Float:mWeight,
	Float:mX,
	Float:mY,
	Float:mZ,
	Float:mrX,
	Float:mrY,
	Float:mrZ,
	Meat[32],
	Model,
	MeatPrice,
	Float:TextX,
	Float:TextY,
	Float:TextZ,
	Float:AreaX,
	Float:AreaY,
	Float:AreaZ
}


new MeatWork[][MeatData] = 
{
	{ 170.0, 190.0, 0.0, 948.180, 2174.149, 1011.801, 84.599, 175.100, 6.899, "Туша корови", 19833, 0, 0.000, 0.750, -1.000, 0.000, 0.750, -1.000 }, 
	{ 170.0, 190.0, 0.0, 948.180, 2167.793, 1011.801, 84.599, 175.100, 6.899, "Туша корови", 19833, 0, 0.000, 0.750, -1.000, 0.000, 0.750, -1.000 }, 
	{ 170.0, 190.0, 0.0, 948.180, 2161.947, 1011.801, 84.599, 175.100, 6.899, "Туша корови", 19833, 0, 0.000, 0.750, -1.000, 0.000, 0.750, -1.000 },
	{ 170.0, 190.0, 0.0, 948.180, 2151.624, 1011.801, 84.599, 175.100, 6.899, "Туша корови", 19833, 0, 0.000, 0.750, -1.000, 0.000, 0.750, -1.000 }, 
	{ 110.0, 130.0, 0.0, 936.027, 2151.885, 1011.619, 0.400, 88.400, 88.500, "Туша оленя", 19315, 0, 0.000, 0.000, -1.000, 0.000, 0.000, -1.000 }, 
	{ 110.0, 130.0, 0.0, 936.027, 2159.092, 1011.619, 0.400, 88.400, 88.500, "Туша оленя", 19315, 0, 0.000, 0.000, -1.000, 0.000, 0.000, -1.000 },
	{ 110.0, 130.0, 0.0, 936.027, 2165.134, 1011.619, 0.400, 88.400, 88.500, "Туша оленя", 19315, 0, 0.000, 0.000, -1.000, 0.000, 0.000, -1.000 },
	{ 110.0, 130.0, 0.0, 936.027, 2174.040, 1011.619, 0.400, 88.400, 88.499, "Туша оленя", 19315, 0, 0.000, 0.000, -1.000, 0.000, 0.000, -1.000 },
	{ 140.0, 160.0, 0.0, 962.434, 2123.039, 1016.605, 0.000, 0.000, 0.000, "Туша свині", 2589, 0, 0.1320, 0.0953, 3.588318, 0.000, 0.000, -7.000 },
	{ 140.0, 160.0, 0.0, 955.954, 2123.039, 1016.605, 0.000, 0.000, 0.000, "Туша свині", 2589, 0, 0.1320, 0.0953, 3.588318, 0.000, 0.000, -7.000 },
	{ 140.0, 160.0, 0.0, 955.954, 2130.602, 1016.605, 0.000, 0.000, 0.000, "Туша свині", 2589, 0, 0.1320, 0.0953, 3.588318, 0.000, 0.000, -7.000 },
	{ 140.0, 160.0, 0.0, 955.954, 2138.456, 1016.605, 0.000, 0.000, 0.000, "Туша свині", 2589, 0, 0.1320, 0.0953, 3.588318, 0.000, 0.000, -7.000 },
	{ 140.0, 160.0, 0.0, 962.434, 2130.849, 1016.605, 0.000, 0.000, 0.000, "Туша свині", 2589, 0, 0.1320, 0.0953, 3.588318, 0.000, 0.000, -7.000 },
	{ 140.0, 160.0, 0.0, 962.434, 2139.842, 1016.605, 0.000, 0.000, 0.000, "Туша свині", 2589, 0, 0.1320, 0.0953, 3.588318, 0.000, 0.000, -7.000 }
};

new MeatPlayer[sizeof(MeatWork)];
new Text3D:MeatText[sizeof(MeatWork)];
new MeatObject[sizeof(MeatWork)];
new MeatFactorySphere;
new MeatSphere[sizeof(MeatWork)];
new MeatWorkInstr[2];
new Text3D:MeatWorkInstrText[2];
new MeatCutTimer[MAX_PLAYERS];
new MeatProgressTimer[MAX_PLAYERS];
new MeatConveyor, MeatConveyor2, MeatWarehouse, MeatConveyorEnd, MeatConveyorEnd2, MeatFactoryTotal, MeatWorkerCount, MeatWorkTime[MAX_PLAYERS];
new Text3D:MeatFactoryTotalText;
new MeatPlayerObject[MAX_PLAYERS], MeatPlayerObject2[MAX_PLAYERS];
new MeatPorkTime, MeatDeerTime, MeatCowTime, MeatRenewalTime;
new Float:MeatPorkPrice, Float:MeatDeerPrice, Float:MeatCowPrice, MeatWorkStatus, MeatWashInstr;

new Float:MeatPlayerArray[MAX_PLAYERS][50];
new MeatCutCount[MAX_PLAYERS];

new ProgressBarTimer[MAX_PLAYERS];
new PlayerText:ProgressBarTD[MAX_PLAYERS][3];

new Text:MeatBarTD[6];
new PlayerText: MeatBarPlayerTD[MAX_PLAYERS][2];

new Text:MeatCowTD[6];
new PlayerText: MeatCowPlayerTD[MAX_PLAYERS][2];

new Text:MeatDeerTD[6];
new PlayerText: MeatDeerPlayerTD[MAX_PLAYERS][2];

new Text: MeatProgressBar[1];
new PlayerText: MeatProgress[MAX_PLAYERS][1];


CB:MeatCut(playerid, part) {
	new process;
	new meat = GetPVarInt(playerid, "MeatPlayer");
	ClearAnimations(playerid);
	SetPVarInt(playerid, "MeatCutProcess", GetPVarInt(playerid, "MeatCutProcess") + 1);
	process = GetPVarInt(playerid, "MeatCutProcess");
	DeletePVar(playerid, "CutProcess");

	for(new i = 3; i < 6; i++) {

		if(GetPVarInt(playerid, "MeatCow")) TextDrawHideForPlayer(playerid, MeatCowTD[i]);
		else if(GetPVarInt(playerid, "MeatDeer")) TextDrawHideForPlayer(playerid, MeatDeerTD[i]);
		else if(GetPVarInt(playerid, "MeatPork")) TextDrawHideForPlayer(playerid, MeatBarTD[i]);
	}

	new textd = random(3);
	switch(textd) {
		case 0: {
			if(GetPVarInt(playerid, "MeatCow")) TextDrawShowForPlayer(playerid, MeatCowTD[5]);
			else if(GetPVarInt(playerid, "MeatDeer")) TextDrawShowForPlayer(playerid, MeatDeerTD[5]);
			else if(GetPVarInt(playerid, "MeatPork")) TextDrawShowForPlayer(playerid, MeatBarTD[5]);
		}
		case 1: {
			if(GetPVarInt(playerid, "MeatCow")) TextDrawShowForPlayer(playerid, MeatCowTD[4]);
			else if(GetPVarInt(playerid, "MeatDeer")) TextDrawShowForPlayer(playerid, MeatDeerTD[4]);
			else if(GetPVarInt(playerid, "MeatPork")) TextDrawShowForPlayer(playerid, MeatBarTD[5]);
		}
		case 2: {
			if(GetPVarInt(playerid, "MeatCow")) TextDrawShowForPlayer(playerid, MeatCowTD[3]);
			else if(GetPVarInt(playerid, "MeatDeer")) TextDrawShowForPlayer(playerid, MeatDeerTD[3]);
			else if(GetPVarInt(playerid, "MeatPork")) TextDrawShowForPlayer(playerid, MeatBarTD[3]);
		}
		case 3: {
			if(GetPVarInt(playerid, "MeatCow")) TextDrawShowForPlayer(playerid, MeatCowTD[5]);
			else if(GetPVarInt(playerid, "MeatDeer")) TextDrawShowForPlayer(playerid, MeatDeerTD[5]);
			else if(GetPVarInt(playerid, "MeatPork")) TextDrawShowForPlayer(playerid, MeatBarTD[5]);
		}
	}
	ClearAnimations(playerid);

	PlayerTextDrawHide(playerid, MeatProgress[playerid][0]);

	new Float:len = 113.00 / MeatCutCount[playerid];

	SetPVarInt(playerid, "MeatTDLen", GetPVarInt(playerid, "MeatTDLen") + len);

	PlayerTextDrawHide(playerid, MeatProgress[playerid][0]);
	PlayerTextDrawTextSize(playerid, MeatProgress[playerid][0], GetPVarInt(playerid, "MeatTDLen"), 3.000);
	PlayerTextDrawShow(playerid, MeatProgress[playerid][0]);

	new Float:weight = MeatPlayerArray[playerid][process];

	/*
	new Float:weight;
	if(GetPVarInt(playerid, "MeatCow")) weight = mathfrandom(6.00, 9.00);
	else if(GetPVarInt(playerid, "MeatDeer")) weight = mathfrandom(3.00, 6.00);
	else if(GetPVarInt(playerid, "MeatPork")) weight = mathfrandom(5.00, 7.00);
	*/

	//if(MeatWork[meat][mWeight] >= 0.00) MeatWork[meat][mWeight] = MeatWork[meat][mWeight] - weight;
	//else if(weight > MeatWork[meat][mWeight] && MeatWork[meat][mWeight] <= 0.00)

	// SendInt(playerid, process);

	// SendFloat(playerid, weight);

	MeatWork[meat][mWeight] = MeatWork[meat][mWeight] - weight;

	if(MeatWork[meat][mWeight] <= 0.00) {
		// weight = weight - MeatWork[meat][mWeight];
		MeatWork[meat][mWeight] = 0.00;
		DestroyDynamic3DTextLabel(MeatText[meat]);
		DestroyDynamicObject(MeatObject[meat]);
		DestroyDynamicArea(MeatSphere[meat]);
		new time = RandomEx(5,8);
		SetTimerEx("MeatRenewal", time * 60000, false, "i", meat, 1);
		MeatPlayer[meat] = INVALID_PLAYER_ID;
		return EndMeatProcess(playerid);
	}


	new string[256];
	format:string("{98FB98}%s\n\n"W"Вага: "G"%.2f фунт(-ів).\n\n"W"Обробляє: "G"%s", MeatWork[meat][Meat], MeatWork[meat][mWeight], CI[playerid][cName]);
	UpdateDynamic3DTextLabelText(MeatText[meat], -1, string);

	format:string("%.2flb.", MeatWork[meat][mWeight]);

	if(GetPVarInt(playerid, "MeatCow")) PlayerTextDrawSetString(playerid, MeatCowPlayerTD[playerid][1], string);
	else if(GetPVarInt(playerid, "MeatDeer")) PlayerTextDrawSetString(playerid, MeatDeerPlayerTD[playerid][1], string);
	else if(GetPVarInt(playerid, "MeatPork")) PlayerTextDrawSetString(playerid, MeatBarPlayerTD[playerid][1], string);

	SetPVarFloat(playerid, "MeatTotal", GetPVarFloat(playerid, "MeatTotal") + weight);

	new td[32];
	format(td, sizeof(td), "%.2f", weight);


	format:string("Ви відрізали шматок м'яса вагою "P"%.2f фунт(-ів)."W" Загальна кількість зрізаного м'яса: "P"%.2f фунт(-ів).", weight, GetPVarFloat(playerid, "MeatTotal"));
	SendInfo(playerid, string);


	// SendInt(playerid, floatround(GetPVarFloat(playerid, "MeatTotal")));
	// SendFloat(playerid, GetPVarFloat(playerid, "MeatTotal"));


	//if(process >= 10) return EndMeatProcess(playerid);

	return 1;
}
stock EndMeatProcess(playerid) 
{
	SetPVarInt(playerid, "EndMeatProc", 1);

	if(GetPVarInt(playerid, "MeatCow")) SetPVarInt(playerid, "MeatCowSalary", 1);
	else if(GetPVarInt(playerid, "MeatDeer")) SetPVarInt(playerid, "MeatDeerSalary", 1);
	else if(GetPVarInt(playerid, "MeatPork")) SetPVarInt(playerid, "MeatPorkSalary", 1);

	for(new i; i < 6; i++) TextDrawHideForPlayer(playerid, MeatBarTD[i]);
	for(new i; i < 6; i++) TextDrawHideForPlayer(playerid, MeatCowTD[i]);
	for(new i; i < 6; i++) TextDrawHideForPlayer(playerid, MeatDeerTD[i]);


	for(new i = 1; i < 50; i++) {
		//MeatPlayerArray[playerid][i] = -1;
		MeatPlayerArray[playerid][i] = INVALID_PLAYER_ID;
	}
	MeatCutCount[playerid] = INVALID_PLAYER_ID;


	PlayerTextDrawHide(playerid, MeatProgress[playerid][0]);

	TogglePlayerControllable(playerid, 1);
	CancelSelectTextDraw(playerid);

	new string[256];
	format(string, sizeof(string), "Ви успішно завершили обробку туші вагою "P"%.2f "W"фунт(-ів).", GetPVarFloat(playerid, "MeatTotal"));
	SendOK(playerid, string);
	SendHint(playerid, "Віднесіть м'ясо на конвеєр для переробки.");

	DeletePVar(playerid, "MeatStarted");
	DeletePVar(playerid, "MeatPlayer");
	DeletePVar(playerid, "MeatTDLen");

	RemovePlayerAttachedObject(playerid, 0);

	SetPVarInt(playerid, "MeatCarry", 1);
	ApplyAnimation(playerid, "CARRY", "liftup105", 1.0, 0, 1, 1, 0, 0, 1);

	SetTimerEx("ccry_partial", 1000, false, "i", playerid);

	new area = RandomEx(1,5);
	switch(area)
	{
		case 1:
		{
			SetPlayerCheckpoint(playerid, 942.3709,2173.1387,1011.0234, 1);
			SetPVarInt(playerid, "MeatConveyor", 1);
		}
		case 2:
		{
			SetPlayerCheckpoint(playerid, 942.4459,2137.2944,1011.0234, 1);
			SetPVarInt(playerid, "MeatConveyor", 2);
		}
		case 3:
		{
			SetPlayerCheckpoint(playerid, 942.4459,2137.2944,1011.0234, 1);
			SetPVarInt(playerid, "MeatConveyor", 2);
		}
		case 4:
		{
			SetPlayerCheckpoint(playerid, 942.4459,2137.2944,1011.0234, 1);
			SetPVarInt(playerid, "MeatConveyor", 2);
		}
		case 5:
		{
			SetPlayerCheckpoint(playerid, 942.3709,2173.1387,1011.0234, 1);
			SetPVarInt(playerid, "MeatConveyor", 1);
		}
	}
	SetPVarInt(playerid, "MeatCarry", 1);

	SetPVarInt(playerid, "LastMeat", GetPVarInt(playerid, "Meat"));
	DeletePVar(playerid, "Meat");

	SetPVarInt(playerid, "MeatCount", GetPVarInt(playerid, "MeatCount") + 1);

	if(GetPVarInt(playerid, "MeatCount") == 3)
	{
		DeletePVar(playerid, "MeatCount");
		SetPVarInt(playerid, "MeatNeedToWashInstr", 1);
	}
	return 1;
}
CB:MeatConveyorT(playerid) {
	SetPVarInt(playerid, "MeatConveyorEnd", 1);
	DeletePVar(playerid, "MeatConveyor");
	DeletePVar(playerid, "MeatCarry");
	SetPlayerCheckpoint(playerid, 942.4107,2153.7458,1011.0234, 1);
	return 1;
}
stock DeletePVars(playerid) {
	// meat factory
	DeletePVar(playerid, "MeatTotal");
	DeletePVar(playerid, "MeatSalary");
	DeletePVar(playerid, "MeatConveyor");
	DeletePVar(playerid, "MeatWarehouse");
	DeletePVar(playerid, "MeatConveyorEnd");
	DeletePVar(playerid, "MeatWorkStarted");
	DeletePVar(playerid, "CutProcess");
	DeletePVar(playerid, "MeatCow");
	DeletePVar(playerid, "MeatPork");
	DeletePVar(playerid, "MeatDeer");
	DeletePVar(playerid, "MeatCarry");
	DeletePVar(playerid, "MeatStarted");
	return 1;
}
CB:ccry_partial(playerid) {
	ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 1, 0, 0, 1, 1, 1);
	if(!IsPlayerAttachedObjectSlotUsed(playerid, 0)) SetPlayerAttachedObject(playerid, 0,2803,1,0.23,0.45,0.00,0.00,92.40,-4.49,0.50,0.50,0.50);
	return 1;
}

CB:MeatProgressT(playerid) {
	if(!GetPVarInt(playerid, "MeatProgressTStarted")) SetPVarInt(playerid, "MeatProgressTStarted", 1);

	switch(GetPVarInt(playerid, "MeatProgressTStarted")) {
		case 1: {
			PlayerTextDrawTextSize(playerid, MeatProgress[playerid][0], 56.50, 3.000);
			PlayerTextDrawShow(playerid, MeatProgress[playerid][0]);
			SetPVarInt(playerid, "MeatProgressTStarted", 2);
		}
		case 2: {
			PlayerTextDrawTextSize(playerid, MeatProgress[playerid][0], 84.75, 3.000);
			PlayerTextDrawShow(playerid, MeatProgress[playerid][0]);
			SetPVarInt(playerid, "MeatProgressTStarted", 3);
		}
		case 3: {
			PlayerTextDrawTextSize(playerid, MeatProgress[playerid][0], 113.00, 3.000);
			PlayerTextDrawShow(playerid, MeatProgress[playerid][0]);
			SetPVarInt(playerid, "MeatProgressTStarted", 4);
		}
		case 4: {
			DeletePVar(playerid, "MeatProgressTStarted");
			KillTimer(MeatProgressTimer[playerid]);
		}
	}
	// SendInt(playerid, GetPVarInt(playerid, "MeatProgressTStarted"));
	return 1;
}


CB:MeatRenewal(i)
{
	new string[256];
	MeatObject[i] = CreateDynamicObject(MeatWork[i][Model], MeatWork[i][mX], MeatWork[i][mY], MeatWork[i][mZ], MeatWork[i][mrX], MeatWork[i][mrY], MeatWork[i][mrZ], 1, 1, -1, 300.00, 300.00);
	new randomweight = mathfrandom(MeatWork[i][minWeight], MeatWork[i][maxWeight]);
	MeatWork[i][mWeight] = randomweight;
	MeatPlayer[i] = INVALID_PLAYER_ID;
	MeatSphere[i] = CreateDynamicSphere(MeatWork[i][mX] + MeatWork[i][AreaX], MeatWork[i][mY] + MeatWork[i][AreaY], MeatWork[i][mZ] + MeatWork[i][AreaZ], 2, 1, 1);
	format(string, sizeof(string), "{98FB98}%s\n\n"W"Вага: "G"%.2f фунт(-ів).\n\n"W"Натисніть ENTER, щоб розпочати обробку.", MeatWork[i][Meat], MeatWork[i][mWeight]);
	MeatText[i] = CreateDynamic3DTextLabel(string, -1, MeatWork[i][mX] + MeatWork[i][TextX], MeatWork[i][mY] + MeatWork[i][TextY], MeatWork[i][mZ] - MeatWork[i][TextZ], 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 1, 1,-1, STREAMER_3D_TEXT_LABEL_SD);
	foreach(new p: Player) {
		if(IsPlayerInDynamicArea(p, MeatFactorySphere)) SendClientMessage(p, -1, "Роботодавець: Нову тушу вивісили для обробки.");
	}
	return 1;
}


stock CreatePlayerMeatArray(playerid, meattype) {
	new Float:x, Float:y;
	switch(meattype) {
		case 1: x = 10.00, y = 14.00;
		case 2: x = 6.00, y = 9.00;
		case 3: x = 8.00, y = 11.00;
	}

	new Float:w, Float:sum, Float:lastsum;
	// weight = mathfrandom(6.00, 9.00);
	//else if(GetPVarInt(playerid, "MeatDeer")) weight = mathfrandom(3.00, 6.00);
	//else if(GetPVarInt(playerid, "MeatPork")) weight = mathfrandom(5.00, 7.00);

	if(MeatCutCount[playerid]) {
		for(new i = 1; i < 50; i++) {
			//MeatPlayerArray[playerid][i] = -1;
			MeatPlayerArray[playerid][i] = INVALID_PLAYER_ID;
		}
		MeatCutCount[playerid] = INVALID_PLAYER_ID;
	}

	new meat = GetPVarInt(playerid, "MeatPlayer");

	for(new a = 1; a < 50; a++) {
		w = mathfrandom(x, y);
		MeatPlayerArray[playerid][a] = w;

		sum = sum + w;

		if(sum >= MeatWork[meat][mWeight]) break;
		MeatCutCount[playerid] = a;
		SendFloat(playerid, MeatPlayerArray[playerid][a]);
		SendInt(playerid, MeatCutCount[playerid]);
		// lastsum = sum;
		// format(array, sizeof(array), "%s\n%d. Weight: %.2f. Sum: %.2f.", array, a, MeatPlayerArray[playerid][a], sum);
	}
	// SendFloat(playerid, lastsum);
	MeatCutCount[playerid]++;
	MeatPlayerArray[playerid][MeatCutCount[playerid]] = MeatWork[meat][mWeight] - lastsum;
	// SendFloat(playerid, MeatPlayerArray[playerid][MeatCutCount[playerid]]);
	// lastsum = lastsum + MeatPlayerArray[playerid][MeatCutCount[playerid]];
	// format(array, sizeof(array), "%s\n%d. Weight: %.2f. Sum: %.2f", array, MeatCutCount[playerid], MeatPlayerArray[playerid][MeatCutCount[playerid]], lastsum);
	// format(array, sizeof(array), "%s\nTotal carcass weight: %.2f. Actions count: %d", array, MeatWork[cow][mWeight], MeatCutCount[playerid]);
	// ShowPlayerDialog(playerid, DIALOG_NONE, DIALOG_STYLE_MSGBOX, "1", array, "1", "1");
	return 1;
}

stock load_meat_work() {
	new string[256], Float:randomweight;
	for(new i; i < sizeof(MeatWork); i++) {
		MeatObject[i] = CreateDynamicObject(MeatWork[i][Model], MeatWork[i][mX], MeatWork[i][mY], MeatWork[i][mZ], MeatWork[i][mrX], MeatWork[i][mrY], MeatWork[i][mrZ], 1, 1, -1, 300.00, 300.00);
		MeatSphere[i] = CreateDynamicSphere(MeatWork[i][mX] + MeatWork[i][AreaX], MeatWork[i][mY] + MeatWork[i][AreaY], MeatWork[i][mZ] + MeatWork[i][AreaZ], 2, 1, 1);
		randomweight = mathfrandom(MeatWork[i][minWeight], MeatWork[i][maxWeight]);
		MeatWork[i][mWeight] = randomweight;
		MeatPlayer[i] = INVALID_PLAYER_ID;
		format(string, sizeof(string), "{98FB98}%s\n\n"W"Вага: "G"%.2f фунт(-ів).\n\n"W"Натисніть ENTER, щоб розпочати обробку.", MeatWork[i][Meat], MeatWork[i][mWeight]);
		MeatText[i] = CreateDynamic3DTextLabel(string, -1, MeatWork[i][mX] + MeatWork[i][TextX], MeatWork[i][mY] + MeatWork[i][TextY], MeatWork[i][mZ] - MeatWork[i][TextZ], 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 1, 1,-1, STREAMER_3D_TEXT_LABEL_SD);
	}
	//MeatNPC = FCNPC_Create("Employer");
	// FCNPC_Spawn(MeatNPC, 95, 960.6542, 2097.6040, 1011.0230);
	CreateDynamicActor(95, 960.6542, 2097.6040, 1011.0230, 0.1075, 1, 100.0, 1, 1, -1);
	CreateDynamic3DTextLabel(W"Роботодавець\n\n"G"ALT", -1, 960.6542, 2097.6040, 1011.0230, 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 1, 1,-1, STREAMER_3D_TEXT_LABEL_SD);

	MeatFactorySphere = CreateDynamicSphere(945.8802, 2128.5337, 1011.0234, 200, 1, 1);

	MeatWorkInstr[0] = CreateDynamicSphere(939.4187, 2177.0251, 1011.0234, 1, 1, 1);
	MeatWorkInstrText[0] = CreateDynamic3DTextLabel(""W"Умивальник\n"G"ALT", -1, 939.4187, 2177.0251, 1011.0234, 3, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 1, 1,-1, STREAMER_3D_TEXT_LABEL_SD);
	MeatWorkInstr[1] = CreateDynamicSphere(944.5671, 2177.0251, 1011.0234, 1, 1, 1);
	MeatWorkInstrText[1] = CreateDynamic3DTextLabel(""W"Умивальник\n"G"ALT", -1, 944.5671, 2177.0251, 1011.0234, 3, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 1, 1,-1, STREAMER_3D_TEXT_LABEL_SD);

	MeatConveyor = CreateDynamicSphere(942.3709, 2173.1387, 1011.0234, 1, 1, 1);
	MeatConveyor2 = CreateDynamicSphere(942.4459, 2137.2944, 1011.0234, 1, 1, 1);
	MeatConveyorEnd = CreateDynamicSphere(942.4107, 2153.7458, 1011.0234, 1, 1, 1);
	MeatConveyorEnd2 = CreateDynamicSphere(942.3775, 2117.9021, 1011.0303, 1, 1, 1);
	MeatWarehouse = CreateDynamicSphere(964.9331, 2160.0940, 1011.0303, 1, 1, 1);

	format(string, sizeof(string), "{98FB98}Склад м'ясокомбінату\n\n"W"%i фунт(-ів)", MeatFactoryTotal);
	MeatFactoryTotalText = CreateDynamic3DTextLabel(string, -1, 964.9331, 2160.0940, 1011.0303, 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 1, 1,-1, STREAMER_3D_TEXT_LABEL_SD);
	return 1;
}
CB: MeatWashingInstr(playerid)
{
	ClearAnimations(playerid);
	DeletePVar(playerid, "MeatNeedToWashInstr");
	RemovePlayerAttachedObject(playerid, 0);
	TogglePlayerControllable(playerid, true);
	SendOK(playerid, "Ви успішно помили ніж та можете продовжити обробку туш.");
	return 1;
}