#if defined _inc_PlayerTextDrawStreamer
	#undef _inc_PlayerTextDrawStreamer
#endif

#if defined _PlayerTDStreamer_included
	#endinput
#endif
#define _PlayerTDStreamer_included

#include <a_samp>
#include <foreach>

#if !defined MAX_PLAYER_TEXTDRAWS
	#define MAX_PLAYER_TEXTDRAWS 512
#endif

#if !defined MAX_TEXTDRAW_STRING
	#define MAX_TEXTDRAW_STRING 1024
#endif


static stock _G(n, p) return (n >> (4 * p)) & 0xF;
static stock _S(&n, p, v) { n = n & ~(0xF << (p * 4)) | (v << (p * 4)); }

#define M_VAL -0xABCDEF
#define M_COMPRESSED_VAL 15

enum
{
	epTD_Alignment,
	epTD_UseBox,
	epTD_Shadow,
	epTD_Outline,
	epTD_Proportional,
	epTD_Selectable,
	epTD_Font
};

enum _:ePlayerTextDrawProperties
{
	PlayerText:epTD_SAMP_ID,

	Float:epTD_Position_X,
	Float:epTD_Position_Y,
	Float:epTD_LetterSize_X,
	Float:epTD_LetterSize_Y,
	Float:epTD_TextSize_X,
	Float:epTD_TextSize_Y,

	Float:epTD_PreviewRot_X,
	Float:epTD_PreviewRot_Y,
	Float:epTD_PreviewRot_Z,
	Float:epTD_Preview_Zoom,

	epTD_Color,
	epTD_BoxColor,
	epTD_BackgroundColor,
	epTD_PreviewModel,
	epTD_PreviewVehCol_1,
	epTD_PreviewVehCol_2
};

new pTextDraws_Compressed[MAX_PLAYERS][MAX_PLAYER_TEXTDRAWS];
new pTextDraws[MAX_PLAYERS][MAX_PLAYER_TEXTDRAWS][_:ePlayerTextDrawProperties];
new Iterator:pTDs[MAX_PLAYERS]<MAX_PLAYER_TEXTDRAWS>;

stock PlayerText:pTD_Create(playerid, Float:x, Float:y, text[])
{
	new id = Iter_Free(pTDs[playerid]);
	if (id == -1) return PlayerText:INVALID_TEXT_DRAW;
	
	Iter_Add(pTDs[playerid], id);
	
	pTextDraws[playerid][id][epTD_SAMP_ID] = PlayerText:INVALID_TEXT_DRAW;

	_S(pTextDraws_Compressed[playerid][id], epTD_UseBox, M_COMPRESSED_VAL);
	_S(pTextDraws_Compressed[playerid][id], epTD_Shadow, M_COMPRESSED_VAL);
	_S(pTextDraws_Compressed[playerid][id], epTD_Outline, M_COMPRESSED_VAL);
	_S(pTextDraws_Compressed[playerid][id], epTD_Font, M_COMPRESSED_VAL);
	_S(pTextDraws_Compressed[playerid][id], epTD_Proportional, M_COMPRESSED_VAL);
	_S(pTextDraws_Compressed[playerid][id], epTD_Selectable, M_COMPRESSED_VAL);
	_S(pTextDraws_Compressed[playerid][id], epTD_Alignment, M_COMPRESSED_VAL);
	
	pTextDraws[playerid][id][epTD_Position_X] = x;
	pTextDraws[playerid][id][epTD_Position_Y] = y;
	pTextDraws[playerid][id][epTD_LetterSize_X] = M_VAL;
	pTextDraws[playerid][id][epTD_LetterSize_Y] = M_VAL;
	pTextDraws[playerid][id][epTD_TextSize_X] = M_VAL;
	pTextDraws[playerid][id][epTD_TextSize_Y] = M_VAL;
	pTextDraws[playerid][id][epTD_Color] = M_VAL;
	pTextDraws[playerid][id][epTD_BoxColor] = M_VAL;
	pTextDraws[playerid][id][epTD_BackgroundColor] = M_VAL;
	pTextDraws[playerid][id][epTD_PreviewModel] = M_VAL;
	pTextDraws[playerid][id][epTD_PreviewRot_X] = M_VAL;
	pTextDraws[playerid][id][epTD_PreviewRot_Y] = M_VAL;
	pTextDraws[playerid][id][epTD_PreviewRot_Z] = M_VAL;
	pTextDraws[playerid][id][epTD_Preview_Zoom] = 1.0;
	pTextDraws[playerid][id][epTD_PreviewVehCol_1] = M_VAL;
	pTextDraws[playerid][id][epTD_PreviewVehCol_2] = M_VAL;
	
	new name[20];
	format(name, sizeof(name), "pTD_s_%i", id);
	SetPVarString(playerid, name, text);
	
	return PlayerText:id;
}

stock pTD_Destroy(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	Iter_Remove(pTDs[playerid], id);

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawDestroy(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID]);
	
	return 1;
}

stock pTD_Show(playerid, PlayerText:text)
{
	static string[MAX_TEXTDRAW_STRING];
	string[0] = EOS;

	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	if (pTextDraws[playerid][id][epTD_SAMP_ID] == PlayerText:INVALID_TEXT_DRAW)
	{
		format(string, sizeof(string), "pTD_s_%i", id);
		GetPVarString(playerid, string, string, sizeof(string));

		pTextDraws[playerid][id][epTD_SAMP_ID] = CreatePlayerTextDraw(playerid, pTextDraws[playerid][id][epTD_Position_X], pTextDraws[playerid][id][epTD_Position_Y], string);
	}
	
	if (pTextDraws[playerid][id][epTD_LetterSize_X] != M_VAL)
		PlayerTextDrawLetterSize(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], pTextDraws[playerid][id][epTD_LetterSize_X], pTextDraws[playerid][id][epTD_LetterSize_Y]);
	
	if (pTextDraws[playerid][id][epTD_TextSize_X] != M_VAL)
		PlayerTextDrawTextSize(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], pTextDraws[playerid][id][epTD_TextSize_X], pTextDraws[playerid][id][epTD_TextSize_Y]);
	
	if (_G(pTextDraws_Compressed[playerid][id], epTD_Alignment) != M_COMPRESSED_VAL)
		PlayerTextDrawAlignment(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], _G(pTextDraws_Compressed[playerid][id], epTD_Alignment));
		
	if (pTextDraws[playerid][id][epTD_Color] != M_VAL)
		PlayerTextDrawColor(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], pTextDraws[playerid][id][epTD_Color]);
	
	if (_G(pTextDraws_Compressed[playerid][id], epTD_UseBox) != M_COMPRESSED_VAL)
		PlayerTextDrawUseBox(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], _G(pTextDraws_Compressed[playerid][id], epTD_UseBox));
		
	if (pTextDraws[playerid][id][epTD_BoxColor] != M_VAL)
		PlayerTextDrawBoxColor(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], pTextDraws[playerid][id][epTD_BoxColor]);
	
	if (_G(pTextDraws_Compressed[playerid][id], epTD_Shadow) != M_COMPRESSED_VAL)
		PlayerTextDrawSetShadow(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], _G(pTextDraws_Compressed[playerid][id], epTD_Shadow));
		
	if (_G(pTextDraws_Compressed[playerid][id], epTD_Outline) != M_COMPRESSED_VAL)
		PlayerTextDrawSetOutline(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], _G(pTextDraws_Compressed[playerid][id], epTD_Outline));
	
	if (pTextDraws[playerid][id][epTD_BackgroundColor] != M_VAL)
		PlayerTextDrawBackgroundColor(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], pTextDraws[playerid][id][epTD_BackgroundColor]);
	
	if (_G(pTextDraws_Compressed[playerid][id], epTD_Font) != M_COMPRESSED_VAL)
		PlayerTextDrawFont(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], _G(pTextDraws_Compressed[playerid][id], epTD_Font));
	
	if (_G(pTextDraws_Compressed[playerid][id], epTD_Proportional) != M_COMPRESSED_VAL)
		PlayerTextDrawSetProportional(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], _G(pTextDraws_Compressed[playerid][id], epTD_Proportional));
	
	if (_G(pTextDraws_Compressed[playerid][id], epTD_Selectable) != M_COMPRESSED_VAL)
		PlayerTextDrawSetSelectable(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], _G(pTextDraws_Compressed[playerid][id], epTD_Selectable));
	
	if (pTextDraws[playerid][id][epTD_PreviewModel] != M_VAL)
		PlayerTextDrawSetPreviewModel(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], pTextDraws[playerid][id][epTD_PreviewModel]);
	
	if (pTextDraws[playerid][id][epTD_PreviewRot_X] != M_VAL)
		PlayerTextDrawSetPreviewRot(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], pTextDraws[playerid][id][epTD_PreviewRot_X], pTextDraws[playerid][id][epTD_PreviewRot_Y], pTextDraws[playerid][id][epTD_PreviewRot_Z], pTextDraws[playerid][id][epTD_Preview_Zoom]);
	
	if (pTextDraws[playerid][id][epTD_PreviewVehCol_1] != M_VAL)
		PlayerTextDrawSetPreviewVehCol(playerid, pTextDraws[playerid][id][epTD_SAMP_ID], pTextDraws[playerid][id][epTD_PreviewVehCol_1], pTextDraws[playerid][id][epTD_PreviewVehCol_2]);
	
	PlayerTextDrawShow(playerid, pTextDraws[playerid][id][epTD_SAMP_ID]);
	
	return 1;
}

stock pTD_Hide(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID]);
		pTextDraws[playerid][id][epTD_SAMP_ID] = PlayerText:INVALID_TEXT_DRAW;
	}
	
	return 1;
}

stock pTD_LetterSize(playerid, PlayerText:text, Float:x, Float:y)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	pTextDraws[playerid][id][epTD_LetterSize_X] = x;
	pTextDraws[playerid][id][epTD_LetterSize_Y] = y;

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawLetterSize(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], x, y);

	return 1;
}

stock pTD_TextSize(playerid, PlayerText:text, Float:x, Float:y)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	pTextDraws[playerid][id][epTD_TextSize_X] = x;
	pTextDraws[playerid][id][epTD_TextSize_Y] = y;

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawTextSize(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], x, y);

	return 1;
}

stock pTD_Alignment(playerid, PlayerText:text, alignment)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	_S(pTextDraws_Compressed[playerid][id], epTD_Alignment, alignment);

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawAlignment(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], alignment);

	return 1;
}

stock pTD_Color(playerid, PlayerText:text, color)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	pTextDraws[playerid][id][epTD_Color] = color;

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawColor(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], color);

	return 1;
}

stock pTD_UseBox(playerid, PlayerText:text, use)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	_S(pTextDraws_Compressed[playerid][id], epTD_UseBox, use);

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawUseBox(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], use);

	return 1;
}

stock pTD_BoxColor(playerid, PlayerText:text, color)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	pTextDraws[playerid][id][epTD_BoxColor] = color;

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawBoxColor(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], color);

	return 1;
}

stock pTD_SetShadow(playerid, PlayerText:text, size)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	_S(pTextDraws_Compressed[playerid][id], epTD_Shadow, size);

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetShadow(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], size);

	return 1;
}

stock pTD_SetOutline(playerid, PlayerText:text, size)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	_S(pTextDraws_Compressed[playerid][id], epTD_Outline, size);

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetOutline(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], size);

	return 1;
}

stock pTD_BackgroundColor(playerid, PlayerText:text, color)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	pTextDraws[playerid][id][epTD_BackgroundColor] = color;

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawBackgroundColor(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], color);

	return 1;
}

stock pTD_Font(playerid, PlayerText:text, font)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	_S(pTextDraws_Compressed[playerid][id], epTD_Font, font);

	if(pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawFont(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], font);

	return 1;
}

stock pTD_SetProportional(playerid, PlayerText:text, set)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	_S(pTextDraws_Compressed[playerid][id], epTD_Proportional, set);

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetProportional(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], set);

	return 1;
}

stock pTD_SetSelectable(playerid, PlayerText:text, set)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	_S(pTextDraws_Compressed[playerid][id], epTD_Selectable, set);

	if(pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetSelectable(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], set);

	return 1;
}

stock pTD_SetString(playerid, PlayerText:text, string[])
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	new name[20];
	format(name, sizeof(name), "pTD_s_%i", id);
	SetPVarString(playerid, name, string);

	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetString(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], string);
		
	return 1;
}

stock pTD_SetPreviewModel(playerid, PlayerText:text, modelindex)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	pTextDraws[playerid][id][epTD_PreviewModel] = modelindex;
	
	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetPreviewModel(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], modelindex);
		
	return 1;
}

stock pTD_SetPreviewRot(playerid, PlayerText:text, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom = 1.0)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	pTextDraws[playerid][id][epTD_PreviewRot_X] = fRotX;
	pTextDraws[playerid][id][epTD_PreviewRot_Y] = fRotY;
	pTextDraws[playerid][id][epTD_PreviewRot_Z] = fRotZ;
	pTextDraws[playerid][id][epTD_Preview_Zoom] = fZoom;
	
	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetPreviewRot(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], fRotX, fRotY, fRotZ, fZoom);
		
	return 1;
}

stock pTD_SetPreviewVehCol(playerid, PlayerText:text, color1, color2)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	pTextDraws[playerid][id][epTD_PreviewVehCol_1] = color1;
	pTextDraws[playerid][id][epTD_PreviewVehCol_2] = color2;
	
	if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
		PlayerTextDrawSetPreviewVehCol(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], color1, color2);
		
	return 1;
}

stock pTD_GetLetterSize(playerid, PlayerText:text, &Float:x, &Float:y)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	x = pTextDraws[playerid][id][epTD_LetterSize_X]
	y = pTextDraws[playerid][id][epTD_LetterSize_Y];

	return 1;
}

stock pTD_GetTextSize(playerid, PlayerText:text, &Float:x, &Float:y)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	x = pTextDraws[playerid][id][epTD_TextSize_X]
	y = pTextDraws[playerid][id][epTD_TextSize_Y];

	return 1;
}

stock pTD_GetAlignment(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return _G(pTextDraws_Compressed[playerid][id], epTD_Alignment);
}

stock pTD_GetColor(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return pTextDraws[playerid][id][epTD_Color];
}

stock pTD_IsBox(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return _G(pTextDraws_Compressed[playerid][id], epTD_UseBox);
}

stock pTD_GetBoxColor(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return pTextDraws[playerid][id][epTD_BoxColor];
}

stock pTD_GetShadow(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return _G(pTextDraws_Compressed[playerid][id], epTD_Shadow);
}

stock pTD_GetOutline(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return _G(pTextDraws_Compressed[playerid][id], epTD_Outline);
}

stock pTD_GetBackgroundColor(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return pTextDraws[playerid][id][epTD_BackgroundColor];
}

stock pTD_GetFont(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return _G(pTextDraws_Compressed[playerid][id], epTD_Font);
}

stock pTD_IsProportional(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return _G(pTextDraws_Compressed[playerid][id], epTD_Proportional);
}

stock pTD_IsSelectable(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return _G(pTextDraws_Compressed[playerid][id], epTD_Selectable);
}

stock pTD_GetString(playerid, PlayerText:text, string[], len = sizeof(string))
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	new name[20];
	format(name, sizeof(name), "pTD_s_%i", id);
	GetPVarString(playerid, name, string, len);

	return 1;
}

stock pTD_GetPreviewModel(playerid, PlayerText:text, modelindex)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return pTextDraws[playerid][id][epTD_PreviewModel];
}

stock pTD_GetPreviewRot(playerid, PlayerText:text, &Float:fRotX, &Float:fRotY, &Float:fRotZ, &Float:fZoom)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	fRotX = pTextDraws[playerid][id][epTD_PreviewRot_X];
	fRotY = pTextDraws[playerid][id][epTD_PreviewRot_Y];
	fRotZ = pTextDraws[playerid][id][epTD_PreviewRot_Z];
	fZoom = pTextDraws[playerid][id][epTD_Preview_Zoom];

	return 1;
}

stock pTD_GetPreviewVehCol(playerid, PlayerText:text, &color1, &color2)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	color1 = pTextDraws[playerid][id][epTD_PreviewVehCol_1];
	color2 = pTextDraws[playerid][id][epTD_PreviewVehCol_2];

	return 1;
}

stock pTD_SetPos(playerid, PlayerText:text, Float:x, Float:y)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	pTextDraws[playerid][id][epTD_Position_X] = x;
	pTextDraws[playerid][id][epTD_Position_Y] = y;

	#if defined _YSF_included
		if (pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW)
			PlayerTextDrawSetPos(playerid, PlayerText:pTextDraws[playerid][id][epTD_SAMP_ID], x, y);
	#endif
	
	return 1;
}

stock pTD_GetPos(playerid, PlayerText:text, &Float:x, &Float:y)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	x = pTextDraws[playerid][id][epTD_Position_X]
	y = pTextDraws[playerid][id][epTD_Position_Y];

	return 1;
}

stock pTD_IsValid(playerid, PlayerText:text)
{
	new id = _:text;
	return Iter_Contains(pTDs[playerid], id);
}

stock pTD_IsVisible(playerid, PlayerText:text)
{
	new id = _:text;
	if (!Iter_Contains(pTDs[playerid], id)) return 0;

	return pTextDraws[playerid][id][epTD_SAMP_ID] != PlayerText:INVALID_TEXT_DRAW;
}


public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	foreach (new i : pTDs[playerid])
	{
		if (pTextDraws[playerid][i][epTD_SAMP_ID] == playertextid)
		{
			#if defined pTD_OnPlayerClickPlayerTD
				pTD_OnPlayerClickPlayerTD(playerid, PlayerText:i);
			#endif
			
			return 1;
		}
	}
	
	return 1;
}

#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw pTD_OnPlayerClickPlayerTD

#if defined pTD_OnPlayerClickPlayerTD
	forward pTD_OnPlayerClickPlayerTD(playerid, PlayerText:playertextid);
#endif


public OnGameModeInit()
{
	Iter_Init(pTDs);

	#if defined pTD_OnGameModeInit
		pTD_OnGameModeInit();
	#endif

	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit pTD_OnGameModeInit

#if defined pTD_OnGameModeInit
	forward pTD_OnGameModeInit();
#endif


public OnPlayerConnect(playerid)
{
	Iter_Clear(pTDs[playerid]);
	
	#if defined pTD_OnPlayerConnect
		pTD_OnPlayerConnect(playerid);
	#endif

	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect pTD_OnPlayerConnect

#if defined pTD_OnPlayerConnect
	forward pTD_OnPlayerConnect(playerid);
#endif


public OnPlayerDisconnect(playerid, reason)
{
	Iter_Clear(pTDs[playerid]);
		
	#if defined pTD_OnPlayerDisconnect
		pTD_OnPlayerDisconnect(playerid, reason);
	#endif
	
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect pTD_OnPlayerDisconnect

#if defined pTD_OnPlayerDisconnect
	forward pTD_OnPlayerDisconnect(playerid, reason);
#endif


#if defined _ALS_CreatePlayerTextDraw
	#undef CreatePlayerTextDraw
#else
	#define _ALS_CreatePlayerTextDraw
#endif
#define CreatePlayerTextDraw pTD_Create

#if defined _ALS_PlayerTextDrawDestroy
	#undef PlayerTextDrawDestroy
#else
	#define _ALS_PlayerTextDrawDestroy
#endif
#define PlayerTextDrawDestroy pTD_Destroy

#if defined _ALS_PlayerTextDrawLetterSize
	#undef PlayerTextDrawLetterSize
#else
	#define _ALS_PlayerTextDrawLetterSize
#endif
#define PlayerTextDrawLetterSize pTD_LetterSize

#if defined _ALS_PlayerTextDrawTextSize
	#undef PlayerTextDrawTextSize
#else
	#define _ALS_PlayerTextDrawTextSize
#endif
#define PlayerTextDrawTextSize pTD_TextSize

#if defined _ALS_PlayerTextDrawAlignment
	#undef PlayerTextDrawAlignment
#else
	#define _ALS_PlayerTextDrawAlignment
#endif
#define PlayerTextDrawAlignment pTD_Alignment

#if defined _ALS_PlayerTextDrawColor
	#undef PlayerTextDrawColor
#else
	#define _ALS_PlayerTextDrawColor
#endif
#define PlayerTextDrawColor pTD_Color

#if defined _ALS_PlayerTextDrawUseBox
	#undef PlayerTextDrawUseBox
#else
	#define _ALS_PlayerTextDrawUseBox
#endif
#define PlayerTextDrawUseBox pTD_UseBox

#if defined _ALS_PlayerTextDrawBoxColor
	#undef PlayerTextDrawBoxColor
#else
	#define _ALS_PlayerTextDrawBoxColor
#endif
#define PlayerTextDrawBoxColor pTD_BoxColor

#if defined _ALS_PlayerTextDrawSetShadow
	#undef PlayerTextDrawSetShadow
#else
	#define _ALS_PlayerTextDrawSetShadow
#endif
#define PlayerTextDrawSetShadow pTD_SetShadow

#if defined _ALS_PlayerTextDrawSetOutline
	#undef PlayerTextDrawSetOutline
#else
	#define _ALS_PlayerTextDrawSetOutline
#endif
#define PlayerTextDrawSetOutline pTD_SetOutline

#if defined _ALS_PlayerTDBackgroundColor
	#undef PlayerTextDrawBackgroundColor
#else
	#define _ALS_PlayerTDBackgroundColor
#endif
#define PlayerTextDrawBackgroundColor pTD_BackgroundColor

#if defined _ALS_PlayerTextDrawFont
	#undef PlayerTextDrawFont
#else
	#define _ALS_PlayerTextDrawFont
#endif
#define PlayerTextDrawFont pTD_Font

#if defined _ALS_PlayerTDSetProportional
	#undef PlayerTextDrawSetProportional
#else
	#define _ALS_PlayerTDSetProportional
#endif
#define PlayerTextDrawSetProportional pTD_SetProportional

#if defined _ALS_PlayerTDSetSelectable
	#undef PlayerTextDrawSetSelectable
#else
	#define _ALS_PlayerTDSetSelectable
#endif
#define PlayerTextDrawSetSelectable pTD_SetSelectable

#if defined _ALS_PlayerTextDrawShow
	#undef PlayerTextDrawShow
#else
	#define _ALS_PlayerTextDrawShow
#endif
#define PlayerTextDrawShow pTD_Show

#if defined _ALS_PlayerTextDrawHide
	#undef PlayerTextDrawHide
#else
	#define _ALS_PlayerTextDrawHide
#endif
#define PlayerTextDrawHide pTD_Hide

#if defined _ALS_PlayerTextDrawSetString
	#undef PlayerTextDrawSetString
#else
	#define _ALS_PlayerTextDrawSetString
#endif
#define PlayerTextDrawSetString pTD_SetString

#if defined _ALS_PlayerTDSetPreviewModel
	#undef PlayerTextDrawSetPreviewModel
#else
	#define _ALS_PlayerTDSetPreviewModel
#endif
#define PlayerTextDrawSetPreviewModel pTD_SetPreviewModel

#if defined _ALS_PlayerTDSetPreviewRot
	#undef PlayerTextDrawSetPreviewRot
#else
	#define _ALS_PlayerTDSetPreviewRot
#endif
#define PlayerTextDrawSetPreviewRot pTD_SetPreviewRot

#if defined _ALS_PlayerTDSetPreviewVehCol
	#undef PlayerTextDrawSetPreviewVehCol
#else
	#define _ALS_PlayerTDSetPreviewVehCol
#endif
#define PlayerTextDrawSetPreviewVehCol pTD_SetPreviewVehCol

#if defined _ALS_PlayerTDGetLetterSize
	#undef PlayerTextDrawGetLetterSize
#else
	#define _ALS_PlayerTDGetLetterSize
#endif
#define PlayerTextDrawGetLetterSize pTD_GetLetterSize

#if defined _ALS_PlayerTextDrawGetTextSize
	#undef PlayerTextDrawGetTextSize
#else
	#define _ALS_PlayerTextDrawGetTextSize
#endif
#define PlayerTextDrawGetTextSize pTD_GetTextSize

#if defined _ALS_PlayerTextDrawGetAlignment
	#undef PlayerTextDrawGetAlignment
#else
	#define _ALS_PlayerTextDrawGetAlignment
#endif
#define PlayerTextDrawGetAlignment pTD_GetAlignment

#if defined _ALS_PlayerTextDrawGetColor
	#undef PlayerTextDrawGetColor
#else
	#define _ALS_PlayerTextDrawGetColor
#endif
#define PlayerTextDrawGetColor pTD_GetColor

#if defined _ALS_PlayerTextDrawIsBox
	#undef PlayerTextDrawIsBox
#else
	#define _ALS_PlayerTextDrawIsBox
#endif
#define PlayerTextDrawIsBox pTD_IsBox

#if defined _ALS_PlayerTextDrawGetBoxColor
	#undef PlayerTextDrawGetBoxColor
#else
	#define _ALS_PlayerTextDrawGetBoxColor
#endif
#define PlayerTextDrawGetBoxColor pTD_GetBoxColor

#if defined _ALS_PlayerTextDrawGetShadow
	#undef PlayerTextDrawGetShadow
#else
	#define _ALS_PlayerTextDrawGetShadow
#endif
#define PlayerTextDrawGetShadow pTD_GetShadow

#if defined _ALS_PlayerTextDrawGetOutline
	#undef PlayerTextDrawGetOutline
#else
	#define _ALS_PlayerTextDrawGetOutline
#endif
#define PlayerTextDrawGetOutline pTD_GetOutline

#if defined _ALS_PlayerTDGetBackgroundCol
	#undef PlayerTextDrawGetBackgroundCol
#else
	#define _ALS_PlayerTDGetBackgroundCol
#endif
#define PlayerTextDrawGetBackgroundCol pTD_GetBackgroundColor

#if defined _ALS_PlayerTextDrawGetFont
	#undef PlayerTextDrawGetFont
#else
	#define _ALS_PlayerTextDrawGetFont
#endif
#define PlayerTextDrawGetFont pTD_GetFont

#if defined _ALS_PlayerTDIsProportional
	#undef PlayerTextDrawIsProportional
#else
	#define _ALS_PlayerTDIsProportional
#endif
#define PlayerTextDrawIsProportional pTD_IsProportional

#if defined _ALS_PlayerTextDrawIsSelectable
	#undef PlayerTextDrawIsSelectable
#else
	#define _ALS_PlayerTextDrawIsSelectable
#endif
#define PlayerTextDrawIsSelectable pTD_IsSelectable

#if defined _ALS_PlayerTextDrawGetString
	#undef PlayerTextDrawSGetString
#else
	#define _ALS_PlayerTextDrawGetString
#endif
#define PlayerTextDrawSetGtring pTD_GetString

#if defined _ALS_PlayerTDGetPreviewModel
	#undef PlayerTextDrawGetPreviewModel
#else
	#define _ALS_PlayerTDGetPreviewModel
#endif
#define PlayerTextDrawGetPreviewModel pTD_GetPreviewModel

#if defined _ALS_PlayerTDGetPreviewRot
	#undef PlayerTextDrawGetPreviewRot
#else
	#define _ALS_PlayerTDGetPreviewRot
#endif
#define PlayerTextDrawGetPreviewRot pTD_GetPreviewRot

#if defined _ALS_PlayerTDGetPreviewVehCol
	#undef PlayerTextDrawGetPreviewVehCol
#else
	#define _ALS_PlayerTDGetPreviewVehCol
#endif
#define PlayerTextDrawGetPreviewVehCol pTD_GetPreviewVehCol

#if defined _ALS_IsValidPlayerTextDraw
	#undef IsValidPlayerTextDraw
#else
	#define _ALS_IsValidPlayerTextDraw
#endif
#define IsValidPlayerTextDraw pTD_IsValid

#if defined _ALS_IsPlayerTextDrawVisible
	#undef IsPlayerTextDrawVisible
#else
	#define _ALS_IsPlayerTextDrawVisible
#endif
#define IsPlayerTextDrawVisible pTD_IsVisible

#if defined _ALS_PlayerTextDrawGetPos
	#undef PlayerTextDrawGetPos
#else
	#define _ALS_PlayerTextDrawGetPos
#endif
#define PlayerTextDrawGetPos pTD_GetPos

#if defined _ALS_PlayerTextDrawSetPos
	#undef PlayerTextDrawSetPos
#else
	#define _ALS_PlayerTextDrawSetPos
#endif
#define PlayerTextDrawSetPos pTD_SetPos
