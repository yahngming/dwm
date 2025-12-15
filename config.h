/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 1;        /* border pixel of windows */
static const unsigned int gappx       = 4;        /* gaps between windows */
static const unsigned int snap        = 8;        /* snap pixel */
static const int showbar              = 1;        /* 0 means no bar */
static const int topbar               = 0;        /* 0 means bottom bar */
static const int barspacing           = 16;       /* spacing between bar and fonts */
static const char *fonts[]            = { "graphical:size=14" };
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
static const char *tags[] = { "", "󰖟", "", "", "󰎞", "", "󰥠", "󰇮", "󰎕", "󰭻" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance   title   tags mask   isfloating   isfullscreen   monitor */
	{  "center",        NULL,      NULL,   0,          1,           0,             -1 },
	{  "fullscreen",    NULL,      NULL,   0,          0,           1,             -1 },
	{  "screensaver",   NULL,      NULL,   0,          0,           1,             -1 },
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0;    /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol    arrange function */
	{ "",      tile              },    /* first entry is default */
	{ "",      monocle           },
	{ "󱂬",      NULL              },    /* no layout function means floating behavior */
};

/* custom symbols for nr. of clients in monocle layout */
/* when clients >= LENGTH(monocles), uses the last element */
static const char *monocles[] = { "󰼏", "󰼐", "󰼑", "󰼒", "󰼓", "󰼔", "󰼕", "󰼖", "󰼗", "󰼘" };

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

/* applications per tag */
static const Arg tagexec[] = {
	{ .v = (const char*[]){"launcher", "-m", dmenumon, NULL} },
	{ .v = (const char*[]){"browser", NULL} },
	{ .v = (const char*[]){"terminal", NULL} },
	{ .v = (const char*[]){"explorer", NULL} },
	{ .v = (const char*[]){"editor", NULL} },
	{ .v = (const char*[]){"tui", "bc -l", NULL} },
	{ .v = (const char*[]){"tui", "cmus", NULL} },
	{ .v = (const char*[]){"tui", "aerc", NULL} },
	{ .v = (const char*[]){"tui", "newsraft", NULL} },
	{ .v = (const char*[]){"tui", "tenere", NULL} }
};

/* autoexec */
static const char *const autoexec[] = {
	"autostart", NULL,
	NULL
};

/* keybidings */
static const Key keys[] = {
	/* modifier                     key              function           argument */
	{ MODKEY,                       XK_a,            spawntag,          {.ui = 1 << 9} },
	{ MODKEY,                       XK_b,            spawntag,          {.ui = 1 << 1} },
	{ MODKEY,                       XK_c,            spawntag,          {.ui = 1 << 5} },
	{ MODKEY,                       XK_d,            spawn,             {.v = (const char*[]){"transmenu", NULL}} },
	{ MODKEY,                       XK_e,            spawntag,          {.ui = 1 << 4} },
	{ MODKEY,                       XK_f,            spawntag,          {.ui = 1 << 3} },
	{ MODKEY,                       XK_h,            spawn,             {.v = (const char*[]){"aboutmenu", NULL}} },
	{ MODKEY,                       XK_i,            spawn,             {.v = (const char*[]){"settings", NULL}} },
	{ MODKEY,                       XK_l,            spawn,             {.v = (const char*[]){"powermenu", NULL}} },
	{ MODKEY,                       XK_m,            spawntag,          {.ui = 1 << 7} },
	{ MODKEY,                       XK_n,            spawntag,          {.ui = 1 << 8} },
	{ MODKEY,                       XK_o,            zoom,              {0} },
	{ MODKEY,                       XK_p,            spawntag,          {.ui = 1 << 6} },
	{ MODKEY,                       XK_q,            killclient,        {0} },
	{ MODKEY,                       XK_r,            spawntag,          {.ui = 1 << 0} },
	{ MODKEY,                       XK_s,            spawn,             {.v = (const char*[]){"screenshot", NULL}} },
	{ MODKEY,                       XK_t,            spawn,             {.v = (const char*[]){"topper", NULL}} },
	{ MODKEY,                       XK_v,            spawn,             {.v = (const char*[]){"clipmenu", NULL}} },
	{ MODKEY,                       XK_z,            spawntag,          {.ui = 1 << 2} },
	{ MODKEY,                       XK_F5,           xrdb,              {.v = NULL} },
	{ MODKEY,                       XK_minus,        spawn,	            {.v = (const char*[]){"volume down", NULL}} },
	{ MODKEY,                       XK_equal,        spawn,	            {.v = (const char*[]){"volume up", NULL}} },
	{ MODKEY,                       XK_Tab,          view,              {0} },
	{ MODKEY,                       XK_BackSpace,    togglefloating,    {0} },
	{ MODKEY,                       XK_Return,       setlayout,         {0} },
	{ MODKEY,                       XK_comma,        focusmon,          {.i = -1} },
	{ MODKEY,                       XK_period,       focusmon,          {.i = +1} },
	{ MODKEY,                       XK_Down,         setmfact,          {.f = -0.05} },
	{ MODKEY,                       XK_Up,           setmfact,          {.f = +0.05} },
	{ MODKEY,                       XK_Left,         focusstack,        {.i = -1} },
	{ MODKEY,                       XK_Right,        focusstack,        {.i = +1} },
	{ MODKEY,                       XK_0,            view,              {.ui = ~0} },
	{ MODKEY|ShiftMask,             XK_j,            incnmaster,        {.i = +1} },
	{ MODKEY|ShiftMask,             XK_k,            incnmaster,        {.i = -1} },
	{ MODKEY|ShiftMask,             XK_comma,        tagmon,            {.i = -1} },
	{ MODKEY|ShiftMask,             XK_period,       tagmon,            {.i = +1} },
	{ MODKEY|ShiftMask,             XK_0,            tag,               {.ui = ~0} },
	TAGKEYS(                        XK_Escape,                          0)
	TAGKEYS(                        XK_grave,                           0)
	TAGKEYS(                        XK_1,                               1)
	TAGKEYS(                        XK_2,                               2)
	TAGKEYS(                        XK_3,                               3)
	TAGKEYS(                        XK_4,                               4)
	TAGKEYS(                        XK_5,                               5)
	TAGKEYS(                        XK_6,                               6)
	TAGKEYS(                        XK_7,                               7)
	TAGKEYS(                        XK_8,                               8)
	TAGKEYS(                        XK_9,                               9)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button2,        spawntag,       {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            0,              Button4,        shiftview,      {.i = -1} },
	{ ClkTagBar,            0,              Button5,        shiftview,      {.i = +1} },
	{ ClkTagBar,            MODKEY,         Button1,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            MODKEY,         Button4,        shiftview,      {.i = -1} },
	{ ClkTagBar,            MODKEY,         Button5,        shiftview,      {.i = +1} },
	{ ClkLtSymbol,          0,              Button1,        view,           {0} },
	{ ClkLtSymbol,          0,              Button3,        view,           {.ui = ~0} },
	{ ClkLtSymbol,          0,              Button4,        setlayout,      {.v = &layouts[1]} },
	{ ClkLtSymbol,          0,              Button5,        setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol,          MODKEY,         Button4,        shiftview,      {.i = -1} },
	{ ClkLtSymbol,          MODKEY,         Button5,        shiftview,      {.i = +1} },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = (const char*[]){"volume toggle", NULL}} },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = (const char*[]){"volume up", NULL}} },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = (const char*[]){"volume down", NULL}} },
	{ ClkStatusText,        MODKEY,         Button4,        shiftview,      {.i = -1} },
	{ ClkStatusText,        MODKEY,         Button5,        shiftview,      {.i = +1} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,         Button4,        shiftview,      {.i = -1} },
	{ ClkClientWin,         MODKEY,         Button5,        shiftview,      {.i = +1} },
	{ ClkRootWin,           0,              Button3,        togglebar,      {0} },
	{ ClkRootWin,           MODKEY,         Button4,        shiftview,      {.i = -1} },
	{ ClkRootWin,           MODKEY,         Button5,        shiftview,      {.i = +1} },
};
