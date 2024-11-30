/* See LICENSE file for copyright and license details. */

/* constants */
#define TERMINAL "st"
#define BROWSER "firefox --profile ~/.config/firefox"

/* appearance */
static const unsigned int borderpx    = 1;        /* border pixel of windows */
static const unsigned int gappx       = 8;        /* gaps between windows */
static const unsigned int snap        = 12;       /* snap pixel */
static const int showbar              = 1;        /* 0 means no bar */
static const int topbar               = 0;        /* 0 means bottom bar */
static const int barspacing           = 16;       /* spacing between bar and fonts */
static const int focusonwheel         = 0;        /* 0 means only focus on click*/
static const char *fonts[]            = { "symbol:size=32" };
static char normbgcolor[]             = "#222222";
static char normbordercolor[]         = "#444444";
static char normfgcolor[]             = "#bbbbbb";
static char selfgcolor[]              = "#eeeeee";
static char selbordercolor[]          = "#005577";
static char selbgcolor[]              = "#005577";
static const unsigned int baralpha    = 0xee;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]        = {
	/*               fg           bg           border          */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};
static const unsigned int alphas[][3] = {
	/*               fg           bg           border      */
	[SchemeNorm] = { OPAQUE,      baralpha,    borderalpha },
	[SchemeSel]  = { OPAQUE,      baralpha,    borderalpha },
};

/* tagging */
static const char *tags[] = { "󰣇", "", "", "󰎞", "", "󰥠", "󰇮", "󰖺", "󰖟" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance    title       tags mask     isfloating   monitor */
	{  NULL,       NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol    arrange function */
	{ "⊞",      tile              },    /* first entry is default */
	{ "🗖",      monocle           },
	{ "❏",      NULL              },    /* no layout function means floating behavior */
};

/* custom symbols for nr. of clients in monocle layout */
/* when clients >= LENGTH(monocles), uses the last element */
static const char *monocles[] = { "➀", "➁", "➂", "➃", "➄", "➅", "➆", "➇", "➈" };

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

/* applications per tag */
static const Arg tagexec[] = {
	{ .v = dmenucmd },
	{ .v = termcmd },
	{ .v = (const char*[]){ TERMINAL, "-e", "lf", NULL } },
	{ .v = (const char*[]){ TERMINAL, "-e", "vim", NULL } },
	{ .v = (const char*[]){ TERMINAL, "-e", "bc", NULL } },
	{ .v = (const char*[]){ TERMINAL, "-e", "cmus", NULL } },
	{ .v = (const char*[]){ TERMINAL, "-e", "aerc", NULL } },
	{ .v = (const char*[]){ "steam", NULL } },
	SHCMD(BROWSER)
};

/* keybidings */
static const Key keys[] = {
	/* modifier                     key              function           argument */
	{ MODKEY,                       XK_space,        spawntag,          {.ui = 1 << 0 } },
	{ MODKEY,                       XK_grave,        spawn,             {.ui = 1 << 1 } },
	{ MODKEY,                       XK_b,            togglebar,         {0} },
	{ MODKEY,                       XK_j,            focusstack,        {.i = +1 } },
	{ MODKEY,                       XK_k,            focusstack,        {.i = -1 } },
	{ MODKEY,                       XK_i,            incnmaster,        {.i = +1 } },
	{ MODKEY,                       XK_d,            incnmaster,        {.i = -1 } },
	{ MODKEY,                       XK_h,            setmfact,          {.f = -0.05} },
	{ MODKEY,                       XK_l,            setmfact,          {.f = +0.05} },
	{ MODKEY,                       XK_o,            zoom,              {0} },
	{ MODKEY,                       XK_q,            killclient,        {0} },
	{ MODKEY|ShiftMask,             XK_q,            spawn,             {.v = (const char*[]){ "xpower", NULL } } },
	{ MODKEY,                       XK_s,            spawn,             SHCMD("maim --hidecursor --select ~/Pictures/screenshots/$(date '+%Y-%m-%d@%H:%M:%S').png | xclip -selection clipboard -target image/png") },
	{ MODKEY,                       XK_Left,         shiftview,         {.i = -1 } },
	{ MODKEY,                       XK_Right,        shiftview,         {.i = +1 } },
	{ MODKEY,                       XK_Down,         setlayout,         {.v = &layouts[0]} },
	{ MODKEY,                       XK_Up,           setlayout,         {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_Down,         setlayout,         {.v = &layouts[2]} },
	{ MODKEY,                       XK_Tab,          view,              {0} },
	{ MODKEY,                       XK_Return,       setlayout,         {0} },
	{ MODKEY|ShiftMask,             XK_Return,       togglefloating,    {0} },
	{ MODKEY,                       XK_comma,        focusmon,          {.i = -1 } },
	{ MODKEY,                       XK_period,       focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,        tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,       tagmon,            {.i = +1 } },
	{ MODKEY,                       XK_minus,        spawn,	            SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-") },
	{ MODKEY,                       XK_equal,        spawn,	            SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+") },
	{ MODKEY,                       XK_BackSpace,    spawn,	            SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") },
	{ MODKEY,                       XK_F5,           xrdb,              {.v = NULL } },
	{ MODKEY,                       XK_0,            view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,            tag,               {.ui = ~0 } },
	TAGKEYS(                        XK_1,                               0)
	TAGKEYS(                        XK_2,                               1)
	TAGKEYS(                        XK_3,                               2)
	TAGKEYS(                        XK_4,                               3)
	TAGKEYS(                        XK_5,                               4)
	TAGKEYS(                        XK_6,                               5)
	TAGKEYS(                        XK_7,                               6)
	TAGKEYS(                        XK_8,                               7)
	TAGKEYS(                        XK_9,                               8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button2,        spawntag,       {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            0,              Button4,        shiftview,      {.i = -1 } },
	{ ClkTagBar,            0,              Button5,        shiftview,      {.i = +1 } },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button2,        killclient,     {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            MODKEY,         Button4,        shiftview,      {.i = -1 } },
	{ ClkTagBar,            MODKEY,         Button5,        shiftview,      {.i = +1 } },
	{ ClkLtSymbol,          0,              Button1,        view,           {0} },
	{ ClkLtSymbol,          0,              Button2,        spawn,          {.v = (const char*[]){ "xpower", NULL } } },
	{ ClkLtSymbol,          0,              Button3,        view,           {.ui = ~0 } },
	{ ClkLtSymbol,          0,              Button4,        setlayout,      {.v = &layouts[1]} },
	{ ClkLtSymbol,          0,              Button5,        setlayout,      {.v = &layouts[0]} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") },
	{ ClkStatusText,        0,              Button4,        spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+") },
	{ ClkStatusText,        0,              Button5,        spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkRootWin,           0,              Button2,        togglebar,      {0} },
	{ ClkRootWin,           0,              Button3,        spawn,          {.v = (const char*[]){ "xwall", NULL } } },
};
