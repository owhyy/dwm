/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define TERMCLASS "St"
#define PrintScreenDWM	    0x0000ff61

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
// static const char *fonts[]          = { "Iosevka Term,Iosevka Nerd Font Mono:pixelsize=14:style=Regular:autohint=true" };
static const char *fonts[]          = { "monospace:pixelsize=14", "JoyPixels:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]          = "monospace:pixelsize=14";
// static const char dmenufont[]       = "Iosevka Term,Iosevka Nerd Font Mono:pixelsize=14:style=Regular:autohint=true";
static const char col_gray1[]       = "#7FB4CA";
static const char col_gray2[]       = "#1F1F28";
static const char col_gray3[]       = "#1F1F28";
static const char col_gray4[]       = "#DCD7BA";
static const char col_cyan[]        = "#7FB4CA";
 // "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray3, "-nf", col_gray4, "-sb", col_cyan, "-sf", col_gray3, NULL

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray3, col_gray2 },
	[SchemeSel]  = { col_gray3, col_cyan, col_gray1 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title            tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,       	    1 << 8,       0,           0,         0,        -1 },
	{ TERMCLASS,  NULL,       NULL,       	    0,            0,           1,         0,        -1 },
	{ TERMINAL,   NULL,       NULL,       	    0,            0,           1,         0,        -1 },
	{ NULL,       NULL,       "Event Tester",   0,            0,           0,         1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "D[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray3, "-nf", col_gray4, "-sb", col_cyan, "-sf", col_gray3, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
#include "push.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("emacs") },
	{ MODKEY,             		      XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,	              	      XK_z,      incrgaps,       {.i = +1 } },
	{ MODKEY,    			              XK_x,      incrgaps,       {.i = -1 } },
	{ MODKEY,		       	            XK_a,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,	       	    XK_a,      defaultgaps,    {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("save_bm") },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("slock") },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             		      XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },
	{ MODKEY,             		      XK_Escape, spawn,     	   SHCMD("resdwm")},
	{ MODKEY,             		      XK_F1,     spawn,     	   SHCMD("switch-layout")},
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask, 	          XK_space,  togglefloating, {0} },
	{ MODKEY,             		      XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ 0, PrintScreenDWM, 		spawn, 		SHCMD("flameshot gui") },
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioMicMute,	spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 10") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 10") },

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
