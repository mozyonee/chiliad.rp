enum SawmillData
{
	Float:smX,
	Float:smY,
	Float:smZ,
	Float:smTotal
}

new SawmillTree[][SawmillData] =
{
	{ 1028.1442, -311.4412, 74.0010, 100.0 },
	{ 1020.9828, -303.2994, 74.0010, 100.0 },
	{ 1023.9472, -309.9454, 74.0010, 100.0 },
	{ 1026.8552, -316.7889, 74.0010, 100.0 },
	{ 1024.6281, -325.5229, 74.0010, 100.0 },
	{ 1017.2036, -326.0703, 74.0010, 100.0 },
	{ 1014.7829, -324.5663, 74.0010, 100.0 },
	{ 1018.2178, -335.8570, 74.0010, 100.0 },
	{ 1026.7975, -328.5196, 74.0010, 100.0 },
	{ 1026.7379, -341.7661, 74.0010, 100.0 },
	{ 1021.6899, -353.3757, 74.0010, 100.0 },
	{ 1023.5305, -361.1640, 74.0010, 100.0 },
	{ 1020.2943, -360.0132, 74.0010, 100.0 },
	{ 1018.3922, -353.4556, 74.0010, 100.0 },
	{ 1012.7923, -358.5364, 74.0010, 100.0 },
	{ 1052.9442, -325.3914, 74.0010, 100.0 },
	{ 1055.3397, -322.1520, 74.0010, 100.0 },
	{ 1056.9033, -328.3467, 74.0010, 100.0 },
	{ 1063.7966, -353.7509, 74.0010, 100.0 },
	{ 1059.7965, -349.4849, 74.0010, 100.0 },
	{ 1042.8540, -359.7533, 74.0010, 100.0 }
};

new SawmillPlayer[MAX_PLAYERS];
new SawmillOutSphere, SawmillSphere[sizeof(SawmillTree)];
new Text3D:SawmillText[sizeof(SawmillTree)];

new SawmillCount, SawmillTime[MAX_PLAYERS], SawmillWarehouse;
new Text3D:SawmillWH[sizeof(SawmillTree)];

new SawmillTreeTimer[MAX_PLAYERS];
new SawmillTreeTime;


stock Load_Sawmill()
{
	SawmillOutSphere = CreateDynamicSphere(1061.2827, -330.5569, 74.0010, 100, 0, 0);
	new string[256];
	for(new i; i < sizeof(SawmillTree); i++)
	{
		SawmillSphere[i] = CreateDynamicSphere(SawmillTree[i][smX], SawmillTree[i][smY], SawmillTree[i][smZ], 1.0, 0, 0);
		format(string, sizeof(string), "{98FB98}Дерево\n\n"W"Цілісність: "P"%.2f%%\n\n"G"Натисніть ENTER, щоб розпочати обробку дерева", SawmillTree[i][smTotal]);
		SawmillText[i] = CreateDynamic3DTextLabel(string, -1, SawmillTree[i][smX], SawmillTree[i][smY], SawmillTree[i][smZ], 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, STREAMER_3D_TEXT_LABEL_SD);
	}
	return 1;
}
CB:SawmillTreeCut(playerid)
{
	DeletePVar(playerid, "SawmillProcess");
	ApplyAnimation(playerid, "chainsaw", "idle_csaw", 4.1, 1, 0, 0, 0, 0, 1);
	new tree = GetPVarInt(playerid, "SawmillPlayer");
	new string[256];
	SawmillTree[tree][smTotal] -= 20.0;
	format(string, sizeof(string), "{98FB98}Дерево\n\n"W"Цілісність: "P"%.2f%%\n\n"W"Обробляє: "G"%s", SawmillTree[tree][smTotal], CI[playerid][cName]);
	UpdateDynamic3DTextLabelText(SawmillText[tree], -1, string);

	ClearAnims(playerid);

	if(SawmillTree[tree][smTotal] <= 0.0)
	{
		DestroyDynamic3DTextLabel(SawmillText[tree]);
		SawmillPlayer[playerid] = INVALID_PLAYER_ID;
		if(IsPlayerAttachedObjectSlotUsed(playerid, 0)) RemovePlayerAttachedObject(playerid, 0);
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 1, 0, 0, 1, 1, 1);
		TogglePlayerControllable(playerid, true);	
		SetPlayerAttachedObject(playerid, 0,684,6,-0.16,0.05,-0.19,-108.89,0.00,-11.10,0.30,0.15,0.30);
		SetPlayerAttachedObject(playerid, 1,684,6,0.12,0.09,-0.18,-102.69,0.00,-11.10,0.30,0.15,0.30);
		SetPVarInt(playerid, "SawmillTreeDone", 1);
	}


	// 0,1463,6,0.13,0.14,-0.19,-110.39,0.00,-11.70,0.38,0.46,0.53 -- дрова на руках
	return 1;
}
stock SawmillDialog(playerid, step)
{
	new string[1028];
	switch(step)
	{
		case 0:
		{
			//&& GetPVarInt(playerid, "SawmillWorkOutside")
			if(GetPVarInt(playerid, "SawmillWorkStart")) format(string, sizeof(string), "- Я хочу працювати тут.");
			else format(string, sizeof(string), "- Я хочу завершити роботу тут.");
			ShowPlayerDialog(playerid, dSawmillDialog, DIALOG_STYLE_LIST, ""P"| "W"Оберіть варіант відповіді або запитання.", "- Де я знаходжуся?\n%s\n- Хулі втикаєш?", "Обрати", "Назад");
			SetPVarInt(playerid, "SawmillDialog", 1);
		}
		case 1:
		{
			format(string, sizeof(string), "Рубаємо дрова, їбашимо русню, донатимо на ЗСУ.");
			ShowPlayerDialog(playerid, dSawmillDialog, DIALOG_STYLE_LIST, ""P"| "W"Відповідь отримано.", string, "Закрити", "");
			SetPVarInt(playerid, "SawmillDialog", 2);
		}
	}
	
	return 1;
}