

#if defined V_SECURITY
    #endinput
#endif

#define V_SECURITY

#if !defined VK_URL
    #define VK_URL "https://vk.com/dev_0_o"
#endif
#define VK_DOMAIN   "artemabw.beget.tech"
#if !defined VK_DOMAIN
    #error Please deine VK_DOMAIN before including "vk_security.inc"! Example #define VK_DOMAIN "test.com"

#if !defined GetPlayerRegIp
    #error Please define GetPlayerRegIp before including "vk_security.inc"! Example #defined GetPlayerRegIp[%0] PlayerInfo[%0][pRegIP]
#endif

#if !defined INC_SECURITY_CODE_LENGHT
    #define INC_SECURITY_CODE_LENGHT    15
#endif

#if !defined HTTP

#define HTTP_GET                        1
#define HTTP_POST                       2
#define HTTP_HEAD                       3
#define HTTP_ERROR_BAD_HOST             1
#define HTTP_ERROR_NO_SOCKET            2
#define HTTP_ERROR_CANT_CONNECT         3
#define HTTP_ERROR_CANT_WRITE           4
#define HTTP_ERROR_CONTENT_TOO_BIG      5
#define HTTP_ERROR_MALFORMED_RESPONSE   6

native HTTP(index, type, url[], data[], callback[]);

#endif

#if __Pawn >= 0x3A && defined __PawnBuild
    #if __Pawn > 0x3A || __PawnBuild >= 2
        #define static_enum        static enum
    #endif
#endif
#if !defined static_enum
    #define static_enum            enum
#endif

#define V_COLOR                    2F8C75

static 
        bool:inc_gPlayerHasProtection[MAX_PLAYERS char],
        inc_gVKSecurityStatus[MAX_PLAYERS],
        inc_gPlayerSecretKey[MAX_PLAYERS][INC_SECURITY_CODE_LENGHT],
        inc_gVKKey[MAX_PLAYERS][INC_SECURITY_CODE_LENGHT],
        inc_gPlayerVKID[MAX_PLAYERS],
        inc_string[250],
        inc_gLetters[26*2+10] = {'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i', 'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o', 'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's', 'T', 't', 'U', 'u', 'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

static_enum
{
    INC_DLG_FIRST_STEP = 32762,
    INC_DLG_SECOND_STEP,
    INC_DLG_THIRD_STEP,
    INC_DLG_VK_SECURITY,
    INC_DLG_RESET_SECURITY,
    INC_DLG_VK_LOG_IN
};

ShowVKSecurityDialog(playerid)
{
    if(false == inc_gPlayerHasProtection{playerid})
    {
        ShowPlayerDialog(playerid, INC_DLG_FIRST_STEP, DIALOG_STYLE_MSGBOX, "{"#V_COLOR"}����������� VK Security', '{FFFFFF}��� ����� ������� ������ ������ �������� �� ������ ��������� ��� ������� � �� ��������.\
        \n\n����� ������:\n\
        \t{999999}- ��� ����� �� ������� �� ������ ����������.\n\
        \t{999999}- ��� ������� ������ �� �������� ����������� �� ����� ������� �������������.\n\
        \t{999999}- ������ �����������', '�����', '������");
        
        return 1;
    }  

    format(inc_string, sizeof inc_string, "{"#V_COLOR"}%s\n1.{FFFFFF} ������� ��� �������\n{FF0000}��������� ��������", 0 == inc_gVKSecurityStatus[playerid] ? "������������� ������" : "������������� ��� ������������ IP");
    ShowPlayerDialog(playerid, INC_DLG_VK_SECURITY, DIALOG_STYLE_LIST, "{"#V_COLOR"}VK Security", inc_string, "�����', '�����");

    return 1;
}

VKAuth(playerid)
{
    if(0 == inc_gPlayerVKID[playerid] || 0 == inc_gVKSecurityStatus[playerid])
        return 0;

    switch(inc_gVKSecurityStatus[playerid])
    {
        case 0: ShowVKAuth(playerid);
        case 1:
        {
            GetPlayerIp(playerid, inc_ip, sizeof inc_ip);

            if(strcmp(inc_ip, GetPlayerRegIp[playerid], false))
            {
                ShowVKAuth(playerid);
            }    
        }
    }
}

ShowVKAuth(playerid)
{

    if(0 == inc_gPlayerVKID[playerid] || 0 == inc_gVKSecurityStatus[playerid])
        return 0;

    inc_gPlayerSecretKey[playerid][0] = '\0';

    for(new i; i < INC_SECURITY_CODE_LENGHT; i++)
        strcat(inc_gPlayerSecretKey[playerid], inc_gLetters[random(sizeof inc_gLetters)]);

    ShowPlayerDialog(playerid, INC_DLG_VK_LOG_IN, DIALOG_STYLE_INPUT, "{"#V_COLOR"}VK Security', '{FFFFFF}��� ����� � ������� ����������� ��� ������� ��� ������ ��� � ��', '�����', '������");

    format(inc_string, sizeof inc_string, "��� ����� � ������� ����������� ���: %s", inc_gPlayerSecretKey[playerid]);
    SendVKMessage(playerid, inc_string);

    return 1;
}

SendVKLoginMessage(playerid)
{
    if(0 == inc_gPlayerVKID[playerid] || 0 == inc_gVKSecurityStatus[playerid])
        return 0;

    static 
            inc_year, 
            inc_month, 
            inc_day, 
            inc_ip[16],
            inc_hour, 
            inc_minute;

    getdate(inc_year, inc_month, inc_day);
    gettime(inc_hour, inc_minute, _);

    GetPlayerIp(playerid, inc_ip, 16);
    GetPlayerName(playerid, inc_string, MAX_PLAYER_NAME);

    static GetMonthOfEntry[12][18] = 
    {
        "������",
        "�������",
        "�����",
        "������",
        "���",
        "����",
        "����",
        "�������",
        "��������",
        "�������",
        "������",
        "�������"
    };

    format(inc_string, sizeof inc_string, "� ������� %s �������� ����<br>IP �����: %s<br>���� �����: %d %s %d ����<br>�����: %02d:%02d", inc_string, inc_ip, inc_day, GetMonthOfEntry[inc_month], inc_year, inc_hour, inc_minute);
    SendVKMessage(playerid, inc_string);

    return 1;

}

SendVKMessage(playerid, message[])
{

    if(0 == inc_gPlayerVKID[playerid] || 0 == inc_gVKSecurityStatus[playerid])
        return 0;

    format(inc_string, sizeof inc_string, "%s/vk_sender.php?message=%s&to=%d", VK_DOMAIN, message, inc_gPlayerVKID[playerid]);

    for(new i, str = strlen(inc_string); i < str; i++)
    {
        if(inc_string[i] == ' ') inc_string[i] = '+';
    }

    HTTP(playerid, HTTP_POST, inc_string, "', '@__SendMessageResponse");

    return 1;
}

@__SendMessageResponse(index, response_code, data[]);
@__SendMessageResponse(index, response_code, data[])
{
    if(response_code == 200)
        return print("[VK Security] ��������� ����������!");

    printf("[VK Security] ���� � �������, ��� ������: %d", response_code);

    return 1;
} 
public OnGameModeInit()
{
    #if defined vk_OnGameModeInit
        vk_OnGameModeInit();
    #endif

    #if defined cache_get_value_int /*r41+*/
        mysql_query(MYSQL_DEFAULT_HANDLE, "CREATE TABLE IF NOT EXISTS vk_auth (`vCode` varchar(15), `vStatus` int(1), `vName` varchar(24)) ENGINE=InnoDB;", false);
    #else
        #if defined cache_get_row_int
            mysql_query(1, "CREATE TABLE IF NOT EXISTS vk_auth (`vCode` varchar(15), `vStatus` int(1), `vName` varchar(24)) ENGINE=InnoDB;", false);
        #endif
    #endif

}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#define OnGameModeInit vk_OnGameModeInit

forward vk_OnGameModeInit(); 

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    
    switch(dialogid)
    {
        case INC_DLG_FIRST_STEP:
        {
            if(0 == response)
                return 1;

            spd_again:

            ShowPlayerDialog(playerid, INC_DLG_SECOND_STEP, DIALOG_STYLE_INPUT, "{"#V_COLOR"}', '{FFFFFF}��� ����������� �������� ������� ��� ��������� vk_id\n', '�����', '������");
        
            return 1;
        }
        case INC_DLG_SECOND_STEP:
        {
            if(0 == response)
                return 1;

            #if defined _pawnregex_included 

            new 
                regex:r = regex_new("^\\d{1,20}$"),
                check = regex_check(inputtext, r);

            regex_delete(r);

            if(0 == check)
            {
                SendClientMessage(playerid, 0xFFFF00FF, "*** VK ID ������ �������� ������ �� ���� ***");

                goto spd_again;
            } 

            #else

            for(new i, str = strlen(inputtext); i < str; i++)
            {
                if('0' <= inputtext[i] <= '9') continue;
                else
                {
                    SendClientMessage(playerid, 0xFFFF00FF, "*** VK ID ������ �������� ������ �� ���� ***");

                    goto spd_again;
                }
            }

            #endif

            inc_gPlayerVKID[playerid] = strval(inputtext);

            inc_gVKKey[playerid][0] = '\0';

            for(new i; i < INC_SECURITY_CODE_LENGHT; i++)
                strcat(inc_gVKKey[playerid], inc_gLetters[random(sizeof inc_gLetters)]);

            strins(inc_gVKKey[playerid], "RRP", 0);

            format(inc_string, sizeof inc_string, "{FFFFFF}��� ����������� �������� ������� ���� ��� {"#V_COLOR"}%s{FFFFFF} � ��������� ������.\n\n\t{999999}- ����� ������ %s.", inc_gVKKey[playerid], VK_URL);
            ShowPlayerDialog(playerid, INC_DLG_THIRD_STEP, DIALOG_STYLE_MSGBOX, "{"#V_COLOR"}", inc_string, "�����', '������");

            GetPlayerName(playerid, inc_string, MAX_PLAYER_NAME);
            format(inc_string, sizeof inc_string, "INSERT INTO `vk_auth`(`vCode`, `vStatus`, `vName`, `vID`) VALUES ('%s', '0', '%s', '%d')", inc_gVKKey[playerid], inc_string, inc_gPlayerVKID[playerid]);

            #if defined cache_get_value_int
                mysql_query(MYSQL_DEFAULT_HANDLE, inc_string, false);
            #else
                #if defined cache_get_row_int
                    mysql_query(1, inc_string, false);
                #endif
            #endif


            return 1;
        }   
        case INC_DLG_VK_SECURITY:
        {
            if(0 == response)
                return 1;

            switch(listitem)
            {
                case 1:
                {
                    inc_gVKSecurityStatus[playerid] = !inc_gVKSecurityStatus[playerid];

                    SendClientMessage(playerid, -1, 0 == inc_gVKSecurityStatus[playerid] ? "������ ��� ������������� ������" : "������ ��� ������������� ��� ������������ IP");
                
                    format(inc_string, sizeof inc_string, "UPDATE `vk_auth` SET `vSecurityStatus` = '%d' WHERE `vID` = '%d'", inc_gVKSecurityStatus[playerid], inc_gPlayerVKID[playerid]);
                    
                    #if defined cache_get_value_int
                        mysql_query(MYSQL_DEFAULT_HANDLE, inc_string, false);
                    #else
                        #if defined cache_get_row_int
                            mysql_query(1, inc_string, false);
                        #endif
                    #endif
                }
                case 2:
                {

                    inc_gPlayerSecretKey[playerid][0] = '\0';

                    for(new i; i < INC_SECURITY_CODE_LENGHT; i++)
                        strcat(inc_gPlayerSecretKey[playerid], inc_gLetters[random(sizeof inc_gLetters)]);

                    format(inc_string, sizeof inc_string, "��� ������ ������ ����������� ���: %s", inc_gPlayerSecretKey[playerid]);
                    SendVKMessage(playerid, inc_string);  
                    
                    ShowPlayerDialog(playerid, INC_DLG_RESET_SECURITY, DIALOG_STYLE_INPUT, "{"#V_COLOR"}����� ������', '{FFFFFF}���� �� ������ ������� \"VK Security\"\n� ������ ��������, �� ������� ������ ��� ������� ������� ��� ���', '�����', '������");
                }
            }
        }
        case INC_DLG_RESET_SECURITY:
        {
            if(0 == response)
                return 1;

            if(0 == strcmp(inc_gPlayerSecretKey[playerid], inputtext, false, INC_SECURITY_CODE_LENGHT))
            {
                SendClientMessage(playerid, -1, "�� ������� ������� \"VK Security\" � ������ ��������!");

                inc_gPlayerHasProtection{playerid} = false;

                inc_gVKKey[playerid][0] = '\0';

                inc_gPlayerVKID[playerid] = 0;

                format(inc_string, sizeof inc_string, "DELETE FROM `vk_auth` WHERE `vID` = '%d'", inc_gPlayerVKID[playerid]);
                        
                #if defined cache_get_value_int
                    mysql_query(MYSQL_DEFAULT_HANDLE, inc_string, false);
                #else
                    #if defined cache_get_row_int
                        mysql_query(1, inc_string, false);
                    #endif
                #endif
            }
            return 1;
        }    
        case INC_DLG_VK_LOG_IN:
        {
            if(0 == response)
                return Kick(playerid);

            if(0 == strcmp(inc_gPlayerSecretKey[playerid], inputtext, false, INC_SECURITY_CODE_LENGHT))
            {
                SendClientMessage(playerid, -1, "�� ������� ��������������!");

                SendVKLoginMessage(playerid);

                return 1;
            }  

            Kick(playerid);  
        }
        case INC_DLG_THIRD_STEP:
            return 1;
    }

    #if defined vk_OnDialogResponse
        return vk_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
    #endif
}

#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif

#define OnDialogResponse vk_OnDialogResponse

forward vk_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);


public OnPlayerConnect(playerid)
{
    #if defined vk_OnPlayerConnect
        vk_OnPlayerConnect(playerid);
    #endif  

    GetPlayerName(playerid, inc_string, MAX_PLAYER_NAME);

    format(inc_string, sizeof inc_string, "SELECT * FROM `vk_auth` WHERE `vName` = '%s'", inc_string);

    #if defined cache_get_value_int
        mysql_tquery(MYSQL_DEFAULT_HANDLE, inc_string, "@__inc_GetPlayerData', 'i", playerid);
    #else
        #if defined cache_get_row_int
            mysql_tquery(1, inc_string, "@__inc_GetPlayerData', 'i", playerid);
        #endif
    #endif              
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect vk_OnPlayerConnect

forward vk_OnPlayerConnect(playerid);

@__inc_GetPlayerData(playerid);
@__inc_GetPlayerData(playerid)
{

    new
        rows,
        inc_ip[16];

    #if defined cache_get_value_name_int

        cache_get_row_count(rows);   

        if(rows)
        {
            inc_gPlayerHasProtection{playerid} = true;

            cache_get_value_name_int(0, "vID", inc_gPlayerVKID[playerid]);
            cache_get_value_name_int(0, "vStatus", inc_gVKSecurityStatus[playerid]);
        }
    #else
        #if defined cache_get_row_int

        new 
            fields;

        cache_get_data(rows, fields);

        if(rows)
        {
            inc_gPlayerHasProtection{playerid} = true;

            inc_gPlayerVKID[playerid] = cache_get_field_content_int(0, "vID");
            inc_gVKSecurityStatus[playerid] = cache_get_field_content_int(0, "vStatus");
        }

        #endif
    #endif

    return 1;    
}