static const char *introTextData =
	"\blThe Powder Toy \bonucular's mod\bl - Mod release number " MTOS(MOD_VERSION) "\n"
	"based on " MTOS(SAVE_VERSION) "." MTOS(MINOR_VERSION) "\n"
	"\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\x7F\n"
	"\bgLook into the README for the shortcuts.\n"
	"\n"
	"\boAdded Elements:\n"
	"\bgRADN (Radon), ENZM (Enzyme), LITH (Lithium), BOLT (Unstable gas), SOIL, MUD, SEED,\n"
	"MGSM (Magnesium), MGMP (Magnesium powder), SSTN (Sandstone), ANT (Langton's Ant),\n"
	"BASE, ROFL, PLST (Plastic), OTWR (One time wire), PLDM (Palladium), FLSH (Flash powder)\n"
	"For more information about the new elements, look at the included 'Introduction' save.\n"
	"\n"
	"\boOther changes:\n"
	"\bg- A few minor changes (SPRK is less glowy, WIFI breaks at higer pressure...)\n"
	"- AMTR is FAR more powerful\n"
	"- mniip's new console was merged (with fixed background color)"
	"\n"
	"\blPlease suggest any element or other stuff you want to see here inside the mods forum thread.\n"
	"Any suggestion is welcome, detailed / already done things are preffered to be added.\n"
	"\n"
    "\boMod created by: \bgnucular\n"
    "\boMod forum thread: \brhttp://tpt.io/.254299\n"
    "\n"
    "\boLua console by: \bgmniip\n"
	"\boOriginal Contributors: \bgStanislaw K Skowronek (Designed the original Powder Toy),\n"
	"\bgSimon Robertshaw, Skresanov Savely, cracker64, Catelite, Bryan Hoyle, Nathan Cousins, jacksonmj,\n"
	"\bgFelix Wallin, Lieuwe Mosch, Anthony Boot, Matthew \"me4502\", MaksProg, jacob1, mniip\n"
	"\n"
#ifndef BETA
	"\bgTo use online features such as saving, you need to register at: \brhttp://powdertoy.co.uk/Register.html\n"
#else
	"\brThis is a BETA, you cannot save things publicly. If you are planning on publishing any saves, use the release version\n"
#endif
	"\n"
	"\bt" MTOS(SAVE_VERSION) "." MTOS(MINOR_VERSION) "." MTOS(BUILD_NUM) " " IDENT_PLATFORM " "
#ifdef X86
	"X86 "
#endif
#ifdef X86_SSE
	"X86_SSE "
#endif
#ifdef X86_SSE2
	"X86_SSE2 "
#endif
#ifdef X86_SSE3
	"X86_SSE3 "
#endif
#ifdef MACOSX
	"MACOSX "
#endif
#ifdef LUACONSOLE
	"LUACONSOLE "
#endif
#ifdef GRAVFFT
	"GRAVFFT "
#endif
#ifdef REALISTIC
	"REALISTIC"
#endif
	;