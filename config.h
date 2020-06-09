/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" ,"Noto Color Emoji:pixelsize=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#1e2021";
static const char col_gray2[]       = "#33384D";
static const char col_font_norm[]   = "#98A9C0";
static const char col_font_bright[] = "#BBD1DA";
static const char col_accent[]      = "#775451";

static const char *colors[][3]      = {
	/*               fg         bg          border   */
	[SchemeNorm] = { col_font_norm, col_gray1,  col_gray2 },
	[SchemeSel]  = { col_font_bright, col_accent, col_accent  },
};

/* tagging */
static const char *tags[] = { "丹", "尼", "尔", "(⚞◕ᆽ◕ฺ⚟)" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "konsole", "konsole",NULL,           0,         0,          1,          -1,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "ǁ",      tile },    /* first entry is default */
	{ "~",      NULL },    /* no layout function means floating behavior */
	{ "o",      monocle },
};

/* key definitions */
#include <X11/XF86keysym.h>

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_font_norm, "-sb", col_accent, "-sf", col_font_bright, NULL };
static const char *termcmd[]  = { "konsole", NULL };

static Key keys[] = {
	/* modifier            key                      function        argument */
	{ MODKEY,              XK_Print,                spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,    XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY,              XK_b,                    togglebar,      {0} },
	{ MODKEY,              XK_Page_Up,              focusstack,     {.i = +1 } },
	{ MODKEY,              XK_Page_Down,            focusstack,     {.i = -1 } },
	{ MODKEY,              XK_Left,                 incnmaster,     {.i = +1 } },
	{ MODKEY,              XK_Right,                incnmaster,     {.i = -1 } },
	{ MODKEY,              XK_Down,                 setmfact,       {.f = -0.05} },
	{ MODKEY,              XK_Up,                   setmfact,       {.f = +0.05} },
	{ MODKEY,              XK_Return,               zoom,           {0} },
	{ MODKEY,              XK_Tab,                  view,           {0} },
	{ MODKEY,              XK_Escape,               killclient,     {0} },
	{ MODKEY,              XK_t,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,              XK_f,                    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,              XK_m,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,              XK_space,                setlayout,      {0} },
	{ MODKEY,		       XK_F11,					togglefullscr,	{0} },
	{ MODKEY|ShiftMask,    XK_space,                togglefloating, {0} },
	{ MODKEY,              XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,    XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY,              XK_comma,                focusmon,       {.i = -1 } },
	{ MODKEY,              XK_period,               focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,    XK_period,               tagmon,         {.i = +1 } },
	{ 0,                   XF86XK_AudioRaiseVolume,	spawn,		    SHCMD("pamixer --allow-boost -i 1; xsetroot -name \"`getStatusBar.sh`\"") },
	{ 0,                   XF86XK_AudioLowerVolume,	spawn,		    SHCMD("pamixer --allow-boost -d 1; xsetroot -name \"`getStatusBar.sh`\"") },
	{ 0,                   XK_Print,	            spawn,		    SHCMD("spectacle") },
	TAGKEYS(               XK_q,                    0)
	TAGKEYS(               XK_d,                    1)
	TAGKEYS(               XK_r,                    2)
	TAGKEYS(               XK_w,                    3)
	{ MODKEY|ShiftMask,    XK_Escape,               quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

