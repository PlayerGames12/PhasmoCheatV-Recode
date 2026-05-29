#pragma once
#include "LanguageManager.h" // Thanks @LingQiao1206 and BitterG for the Chinese translation

inline void RegisterAllTranslations()
{
    // Base errors
    ADD_STR("NeedToBeInGame", "You need to be in the game.", u8"Вам нужно быть в игре.", u8"局内才能使用此功能");
    ADD_STR("NeedMustBeHost", "You must be the host to use this feature.", u8"Вам нужно быть хостом дабы использовать эту функцию.", u8"您必须是房主才能使用此功能");
    ADD_STR("WarnNeedReportDev", "WARNING! Please report this error to the author immediately! By providing logs", u8"ВНИМАНИЕ! Пожалуйста, немедленно сообщите об этой ошибке автору! Предоставив логи", u8"警告！请立即向作者报告此错误，并提供日志文件！");

    // Feature Manager
    ADD_STR("SearchFeatures", "Search features...", u8"Поиск функций...", u8"搜索功能中……");
    ADD_STR("NoFeaturesFound", "No features found matching '%s'", u8"Функции, соответствующие '%s', не найдены", u8"未找到包含 '%s' 的功能");
    ADD_STR("Unknown", "Unknown", u8"Неизвестно", u8"未知");
    ADD_STR("Visuals", "Visuals", u8"Визуалы", u8"视觉效果");
    ADD_STR("Players", "Players", u8"Игроки", u8"玩家");
    ADD_STR("Ghost", "Ghost", u8"Призрак", u8"鬼魂");
    ADD_STR("Cursed", "Cursed Items", u8"Проклятые предметы", u8"诅咒道具");
    ADD_STR("Movement", "Movement", u8"Движение", u8"移动");
    ADD_STR("Misc", "Misc", u8"Разное", u8"杂项");
    ADD_STR("Configs", "Configs", u8"Конфиги", u8"配置");
    ADD_STR("Difficulty", "Difficulty", u8"Сложность", u8"游戏难度");
    ADD_STR("Map", "Map", u8"Карта", u8"地图");
    ADD_STR("BackToCategories", "Back to Categories", u8"Вернуться к категориям", u8"返回");

    // Main Menu
    ADD_STR("Menu_Features", "FEATURES", u8"ФУНКЦИИ", u8"功能");
    ADD_STR("Menu_Settings", "SETTINGS", u8"НАСТРОЙКИ", u8"设置");
    ADD_STR("Menu_About", "ABOUT", u8"О МОДИФИКАЦИИ", u8"关于");
    ADD_STR("Menu_Hotkeys", "Hotkeys", u8"Бинды", u8"快捷键");
    ADD_STR("Menu_Unload", "UNLOAD CHEAT", u8"ВЫГРУЗИТЬ ЧИТ", u8"关闭作弊功能");
    ADD_STR("Menu_General", "General Settings", u8"Общие настройки", u8"常规设置");
    ADD_STR("Menu_ToggleKey", "Menu Toggle Key:", u8"Клавиша меню:", u8"菜单快捷键：");
    ADD_STR("Menu_SetKey", "Set New Key", u8"Задать клавишу", u8"点击设置新快捷键");
    ADD_STR("Menu_PressKey", "Press any key to set as menu toggle...", u8"Нажмите любую клавишу для назначения меню", u8"请按任意键以将其设置为快捷键……");
    ADD_STR("Menu_Cancel", "Cancel", u8"Отмена", u8"取消");
    ADD_STR("Menu_NoFeatures", "Features not available", u8"Функции недоступны", u8"此功能目前不可用");
    ADD_STR("Menu_OpenSource", "OPEN SOURCE", u8"ОТКРЫТЫЙ ИСХОДНЫЙ КОД", u8"开源项目");
    ADD_STR("Menu_GitHubRepo", "GitHub Repository", u8"Репозиторий GitHub", u8"本项目的GitHub仓库");
    ADD_STR("Menu_OpenGitHub", "Open GitHub", u8"Открыть GitHub", u8"打开GitHub查看");
    ADD_STR("Menu_License", "License: MIT", u8"Лицензия: MIT", u8"开源许可证：MIT");
    ADD_STR("Menu_OpenSourceDesc",
        "This project is open source and available under MIT License. Feel free to contribute!",
        u8"Этот проект имеет открытый исходный код и распространяется по лицензии MIT. Вы можете внести вклад!",
        u8"本项目基于 MIT 许可证进行开源，欢迎来贡献代码！");
    ADD_STR("Menu_Credits", "CREDITS", u8"КОМАНДА", u8"制作人员");
    ADD_STR("Menu_SpecialThanks", "Special Thanks", u8"Отдельная благодарность", u8"特别鸣谢");
    ADD_STR("Menu_CheatInjected", "Cheat injected successfully. The menu opens on ", u8"Чит введен успешно. Меню откроется на ", u8"修改器注入成功，打开菜单请按");
    ADD_STR("Menu_ClearCache", "Clear the cache", u8"Очистить кэш", u8"清除缓存");
    ADD_STR("Menu_IsBlur", "Blur menu", u8"Размывать меню", u8"背景模糊");
    ADD_STR("Menu_IsRain", "Rain effect", u8"Эффект дождя", u8"雨天特效");
    ADD_STR("Menu_SettText", "Menu settings", u8"Настройки меню", u8"菜单设置");
    ADD_STR("Menu_ApplyColors", "Apply colors", u8"Применить цвета", u8"应用颜色");
    ADD_STR("Menu_ResetColors", "Reset colors", u8"Сбросить цвета", u8"重置颜色");
    ADD_STR("Menu_SetMenuKey", "Set menu opening key", u8"Задать клавишу открытия меню", u8"设置菜单开启按键");
    ADD_STR("Proxy_Unload", "Proxy don't support \nunloading. Please close \nthe game to exit.", u8"Прокси-режим не поддерживает \nвыгрузку. Пожалуйста, \nзакройте игру, чтобы выйти.", u8"代理模式下不支持卸载\n请关闭游戏以退出");
    ADD_STR("Menu_Language_EN", "EN", u8"Английский", u8"英文");
    ADD_STR("Menu_Language_RU", "RU", u8"Русский", u8"俄语");
    ADD_STR("Menu_Language_CN", "CN", u8"Китайский", u8"中文");
    ADD_STR("Menu_DownloadOurChineseFont", "Download Our Chinese Font", u8"Скачать наш китайский шрифт", u8"下载由我们提供的中文字体");
    ADD_STR("Menu_DiscordRPC", "Enable Discord RPC", u8"Включить Discord RPC", u8"启用 Discord RPC");
    ADD_STR("Menu_RPCShowName", "Show player name in RPC", u8"Показывать имя игрока в RPC", u8"在 RPC 中显示玩家名称");
	ADD_STR("Menu_KeyReserved", "This key is reserved by cheat. Please choose another one.", u8"Эта клавиша зарезервирована читом. Пожалуйста, выберите другую.");

    // Map modifier
    ADD_STR("AutoSelectMap", "Auto Select Map", u8"Автоматический выбор карты", u8"自动选择地图");
    ADD_STR("SelectMap", "Select Map", u8"Выбрать карту", u8"请选择地图");
    ADD_STR("CurrentMap", "Current Map %s", u8"Текущая карта %s", u8"当前地图是%s");
    ADD_STR("EnableMapModifier", "Enable Map Modifier", u8"Включить модификатор карты", u8"启用地图修改功能");
    ADD_STR("CustomMaxLights", "Custom max lights", u8"Пользовательский лимит ламп", u8"自定义最大灯光数");
    ADD_STR("MaxLights", "Max lights", u8"Макс. ламп", u8"最大灯光数");
    ADD_STR("ActivateAllLights", "Activate all lights switches", u8"Включить все выключатели света", u8"开启所有灯的开关");
    ADD_STR("DeactivateAllLights", "Deactivate all lights switches", u8"Выключить все выключатели света", u8"关闭所有灯的开关");
    ADD_STR("TriggerLightning", "Trigger lightning", u8"Вызвать молнию", u8"触发闪电效果（慎用）");
    ADD_STR("SwitchFuseBox", "Switch fuse box", u8"Переключить щиток", u8"开启或关闭电闸");
    ADD_STR("AllLightsActivated", "All light switches activated.", u8"Все выключатели света включены.", u8"所有灯光均已开启");
    ADD_STR("AllLightsDeactivated", "All light switches deactivated.", u8"Все выключатели света выключены.", u8"所有灯光均已关闭");
    ADD_STR("LightningTriggered", "Lightning has been triggered.", u8"Молния была вызвана.", u8"闪电效果已触发");
    ADD_STR("FuseBoxSwitched", "Fuse box has been switched.", u8"Щиток переключён.", u8"电闸状态已改变");
    ADD_STR("WeatherShouldBeHeavyRain", "The weather should be heavy rain.", u8"Погода должна быть сильным дождём.", u8"必须是暴雨天气才能生效");

    // Activity Monitor
    ADD_STR("EnableActivityMonitor", "Enable Activity Monitor", u8"Включить монитор активности", u8"启用鬼魂活动强度监视器");

    // AntiKick
    ADD_STR("AntiKickEnable", "Enable AntiKick", u8"Включить AntiKick", u8"启用防踢出功能");
    ADD_STR("HostKickedYou", "The host tried to kick you out!", u8"Хост попытался кикнуть вас!", u8"房主试图将您踢出游戏！");

    // CursedItemsControll
    ADD_STR("BreakCursed", "Break cursed items##cursed", u8"Сломать проклятые предметы##cursed", u8"破坏诅咒道具##cursed");
    ADD_STR("UseCursed", "Use cursed items##cursed", u8"Использовать проклятые предметы##cursed", u8"使用诅咒道具##cursed");
    ADD_STR("TarotCardsModEnable", "Active tarot cards modifier##cursed", u8"Активировать модификации таро карт##cursed", u8"启用塔罗牌修改器##cursed");
    ADD_STR("ForceTarotCards", "Force Card Type##cursed", u8"Подменить тип карты##cursed", u8"强制设置塔罗牌的类型##cursed");
    ADD_STR("CardType", "Card Type##cursed", u8"Тип карты##cursed", u8"请选择塔罗牌的类型##cursed");
    ADD_STR("InfTarotCards", "Infinite cards##cursed", u8"Бесконечные карты##cursed", u8"无限塔罗牌##cursed");
    ADD_STR("SummoningCircleNotFound", "Summoning Circle not found!", u8"Круг призыва не найден!", u8"未找到召唤阵！");
    ADD_STR("LocalPlayerNotFound", "Local player not found!", u8"Локальный игрок не найден!", u8"未找到本地玩家！");
    ADD_STR("SummoningCircleTransformNotFound", "Summoning Circle transform not found!", u8"Transform круга призыва не найден!", u8"未找到召唤阵的坐标数据！");
    ADD_STR("TooFarFromSummoningCircle", "Too far from the summoning circle", u8"Слишком далеко от круга призыва", u8"距离召唤阵太远");
    ADD_STR("NotEnoughSanity", "Not enough sanity", u8"Не хватает расудка", u8"理智值不足");
    ADD_STR("LitAllCandles", "You have lit a total of: %i candles", u8"Вы зажгли всего: %i свечей", u8"你总共点燃了：%i根蜡烛");
    ADD_STR("UseMusicBox", "Use music box", u8"Использовать музыкальную шкатулку", u8"使用八音盒");
    ADD_STR("FixMusicBox", "Fix music box (SP)", u8"Починить музкальную шкатулку (SP)", u8"修复八音盒（仅限单人游戏）");
    ADD_STR("RitualStarted", "Ritual started", u8"Ритуал запущен", u8"召唤仪式已开始");
    ADD_STR("StartRitual", "Start ritual of the summoning circle", u8"Начать ритуал круга призыва", u8"开始召唤阵仪式");
    ADD_STR("DisableHeartPin", "Disable heart pin", u8"Отключить пин сердца", u8"禁用会刺入巫毒娃娃心脏的图钉");
    ADD_STR("BeginRitualSummoningCircle", "Begin ritual summoning circle", u8"Начать ритуал круга призыва", u8"开始召唤阵仪式");

    // CustName
    ADD_STR("SetName", "Set name##custname", u8"Установить имя##custname", u8"确认设置名称##custname");

    // CustomLookLimits
    ADD_STR("LookLimitsEnable", "Enable Custom Look Limits", u8"Включить пользовательские ограничения на просмотр", u8"启用自定义视角限制");
    ADD_STR("NoLimits", "No Limits", u8"Отключить ограничения", u8"无限制");
    ADD_STR("MinX", "Min X", u8"Минимальный X", u8"最小X值");
    ADD_STR("MaxX", "Max X", u8"Максимальный X", u8"最大X值");

    // Custom speed
    ADD_STR("CustomSpeedEnabled", "Enable custom speed##custSpeed", u8"Включить пользовательскую скорость##custSpeed", u8"启用自定义速度##custSpeed");
    ADD_STR("CustomSpeedSlider", "Custom speed##custSpeed", u8"Пользовательская скорость##custSpeed", u8"请设置速度##custSpeed");

    // Ghost spin
    ADD_STR("GhostSpin_Header", "Ghost Spin", u8"Вращение призрака", u8"旋转鬼魂");
    ADD_STR("GhostSpinEnabled", "Enable ghost spin##ghostSpin", u8"Включить вращение призрака##ghostSpin", u8"启用旋转鬼魂##ghostSpin");
    ADD_STR("GhostSpinSpeed", "Spin speed##ghostSpin", u8"Скорость вращения##ghostSpin", u8"旋转速度##ghostSpin");

    // Difficulty 
    ADD_STR("RequiredLevel", "RequiredLevel", u8"Требуемый уровень", u8"所需等级");
    ADD_STR("SanityPillRestoration", "SanityPillRestoration", u8"Восстановление санпайлов", u8"醒脑丸恢复理智量");
    ADD_STR("StartingSanity", "StartingSanity", u8"Начальное рассудка", u8"初始理智");
    ADD_STR("SanityDrain", "SanityDrain", u8"Скорость потери рассудка", u8"理智降低速度");
    ADD_STR("Sprinting", "Sprinting", u8"Спринт", u8"奔跑");
    ADD_STR("Flashlights", "Flashlights", u8"Фонарики", u8"手电筒");
    ADD_STR("LoseItemsOnDeath", "LoseItemsOnDeath", u8"Потеря предметов при смерти", u8"死亡时丢失物品和消耗品");
    ADD_STR("PlayerSpeed", "PlayerSpeed", u8"Скорость игрока", u8"玩家移动速度");
    ADD_STR("EvidenceGiven", "EvidenceGiven", u8"Количество улик", u8"给出的证据数量");
    ADD_STR("ChangingFavouriteRoom", "ChangingFavouriteRoom", u8"Смена любимой комнаты", u8"变更鬼魂房间");
    ADD_STR("InteractionAmount", "InteractionAmount", u8"Количество взаимодействий", u8"活动等级");
    ADD_STR("EventFrequency", "EventFrequency", u8"Частота событий", u8"事件频率");
    ADD_STR("HuntDuration", "HuntDuration", u8"Длительность охоты", u8"猎杀时间");
    ADD_STR("GracePeriod", "GracePeriod", u8"Период безопасности", u8"猎杀徘徊期");
    ADD_STR("FingerprintChance", "FingerprintChance", u8"Шанс отпечатков", u8"指纹出现几率");
    ADD_STR("FingerprintDuration", "FingerprintDuration", u8"Длительность отпечатков", u8"指纹持续时间");
    ADD_STR("FriendlyGhost", "FriendlyGhost", u8"Дружелюбный призрак", u8"友善的鬼");
    ADD_STR("KillsExtendHunt", "KillsExtendHunt", u8"Убийства продлевают охоту", u8"击杀延长猎杀");
    ADD_STR("RoamingFrequency", "RoamingFrequency", u8"Частота блуждания", u8"游荡频率");
    ADD_STR("GhostSpeed", "GhostSpeed", u8"Скорость призрака", u8"鬼魂速度");
    ADD_STR("SetupTime", "SetupTime", u8"Время подготовки", u8"部署时间");
    ADD_STR("SelectedWeather", "SelectedWeather", u8"Выбранная погода", u8"天气");
    ADD_STR("DoorsOpen", "DoorsOpen", u8"Открытые двери", u8"开局敞开的门");
    ADD_STR("HidingPlaces", "HidingPlaces", u8"Укрытия", u8"躲藏点");
    ADD_STR("SanityMonitor", "SanityMonitor", u8"Монитор рассудка", u8"理智显示屏");
    ADD_STR("ActivityMonitor", "ActivityMonitor", u8"Монитор активности", u8"活动强度显示屏");
    ADD_STR("FuseBoxVisible", "FuseBoxVisible", u8"Щиток виден", u8"显示电闸位置");
    ADD_STR("FuseBoxStartPower", "FuseBoxStartPower", u8"Начальное состояние щитка", u8"电闸初始状态");
    ADD_STR("EnableDifficultyModifier", "Enable Difficulty Modifier", u8"Включить модификатор сложности", u8"启用难度修改器");
    ADD_STR("AddSettingToModify", "Add setting to modify", u8"Добавить параметр для изменения", u8"添加要修改的设置");
    ADD_STR("AddSetting", "Add", u8"Добавить", u8"添加");
    ADD_STR("SelectedSettings", "Selected settings", u8"Выбранные параметры", u8"已选设置");
    ADD_STR("ApplyChanges", "Apply changes", u8"Применить изменения", u8"应用更改");
    ADD_STR("ClearAll", "Clear all", u8"Очистить всё", u8"清除全部");
    ADD_STR("LevelValuesNotFound", "Level values not found", u8"LevelValues не найден", u8"未找到难度等级数据");
    ADD_STR("NoCurrentDifficulty", "No current difficulty", u8"Текущая сложность отсутствует", u8"当前无难度设置");
    ADD_STR("DifficultySettingsApplied", "Difficulty settings applied", u8"Настройки сложности применены", u8"已应用难度设置");
    ADD_STR("FailedApplyDifficultySettings", "Failed to apply difficulty settings", u8"Ошибка применения настроек сложности", u8"应用难度设置失败");
    ADD_STR("Off", "Off", u8"Выключено", u8"关闭");
    ADD_STR("On", "On", u8"Включено", u8"开启");
    ADD_STR("Infinite", "Infinite", u8"Бесконечно", u8"无限");
    ADD_STR("None", "None", u8"Нет", u8"无");
    ADD_STR("Low", "Low", u8"Низкий", u8"低");
    ADD_STR("Medium", "Medium", u8"Средний", u8"中");
    ADD_STR("High", "High", u8"Высокий", u8"高");
    ADD_STR("VeryHigh", "Very High", u8"Очень высокий", u8"非常高");
    ADD_STR("Random", "Random", u8"Случайно", u8"随机");
    ADD_STR("LightRain", "Light rain", u8"Лёгкий дождь", u8"小雨");
    ADD_STR("HeavyRain", "Heavy rain", u8"Сильный дождь", u8"暴雨");
    ADD_STR("Snow", "Snow", u8"Снег", u8"下雪");
    ADD_STR("Wind", "Wind", u8"Ветер", u8"刮风");
    ADD_STR("Clear", "Clear", u8"Ясно", u8"晴朗");
    ADD_STR("Fog", "Fog", u8"Туман", u8"起雾");
    ADD_STR("Sunrise", "Sunrise", u8"Рассвет", u8"日出");
    ADD_STR("BloodMoon", "Blood moon", u8"Кровавая луна", u8"血月");
    ADD_STR("Broken", "Broken", u8"Сломан", u8"损坏");

    // DoorMod
    ADD_STR("EnableDoorModifier", "Enable Door Modifier", u8"Включить модификацию дверей", u8"启用门修改器");
    ADD_STR("DisableDoorInteraction", "Disable Door Interaction", u8"Отключить взаимодействие с дверьми", u8"禁用门互动");
    ADD_STR("EnableDoorInteraction", "Enable Door Interaction", u8"Включить взаимодействие с дверьми", u8"启用门互动");
    ADD_STR("TeleportDoorsToPlayer", "Teleport Doors To Player (only client)", u8"Телепортировать двери к игроку (только клиент)", u8"把所有门传送到玩家位置（仅限客户端）");
    ADD_STR("DisableAllDoors", "Disable All Doors", u8"Отключить все двери", u8"禁用所有的门");
    ADD_STR("EnableAllDoors", "Enable All Doors", u8"Включить все двери", u8"启用所有的门");
    ADD_STR("DoorInteractionEnabled", "Door interaction is enabled.", u8"Взаимодействие с дверьми было включено.", u8"门互动功能已启用");
    ADD_STR("DoorInteractionDisabled", "Door interaction is disabled.", u8"Взаимодействие с дверьми было отключено.", u8"门互动功能已禁用");
    ADD_STR("DoorsTeleported", "Doors teleported to player.", u8"Двери были телепортированы к игроку.", u8"所有门已传送到玩家位置");
    ADD_STR("AllDoorsDisabled", "All doors disabled.", u8"Все двери отключены.", u8"所有的门已禁用");
    ADD_STR("AllDoorsEnabled", "All doors enabled.", u8"Все двери включены.", u8"所有的门已启用");
    ADD_STR("RagdollDoors", "Ragdoll doors", u8"Двери как тряпичные куклы"); // dont use
    ADD_STR("AutoOpenDoors_Done", "All doors opened by modification.", u8"Все двери были открыты модификацией.", u8"所有的门已通过修改器打开");
    ADD_STR("OpenAllDoors", "Auto open all doors", u8"Автоматически открыть все двери", u8"自动打开所有门");

    // Evidence ESP
    ADD_STR("EnableEvidenceESP", "Enable Evidence ESP", u8"Включить ESP улик", u8"启用证据高亮显示");
    ADD_STR("CursedItem", "Cursed item", u8"Проклятые предметы", u8"诅咒道具");
    ADD_STR("DNAEvidence", "DNA evidence", u8"DNA-улики", u8"骨头证据");
    ADD_STR("EMFSpots", "EMF spots", u8"EMF-источники", u8"产生EMF的点位");
    ADD_STR("GhostOrb", "Ghost Orb", u8"Призрачный огонёк", u8"灵球");
    ADD_STR("OtherEvidence", "Other evidence", u8"Прочие улики", u8"其他证据");
    ADD_STR("Color", "Color", u8"Цвет", u8"颜色");

    // ExitVanSolo
    ADD_STR("EnableExitVanSolo", "Enable exit van solo", u8"Включить выход в фургоне одному", u8"启用单人上车离开");

    // ForceStart
    ADD_STR("EnableForceStart", "Enable Force Start", u8"Включить быстрый старт", u8"启用强制开始");

    // FoVEditor
    ADD_STR("EnableCustomFoV", "Enable custom FoV", u8"Включить пользовательское FoV", u8"启用自定义视野");
    ADD_STR("CustomFoVValue", "Custom FoV Value", u8"Пользовательское значение FoV", u8"请设置视野值");
    ADD_STR("ForceApply", "Force Apply", u8"Моментальное применение", u8"强制应用");
    ADD_STR("ResetToDefault", "Reset to Default", u8"Сбросить по умолчанию", u8"重置为默认值");

    // Fullbright
    ADD_STR("EnableFullbright", "Enable Fullbright", u8"Включить Fullbright", u8"启用高亮模式");
    ADD_STR("LightIntensity", "Intensity", u8"Интенсивность", u8"灯光强度");
    ADD_STR("LightRange", "Range", u8"Дальность", u8"光照范围");

    // FuseEsp
    ADD_STR("EnableFuseboxEsp", "Enable fusebox esp", u8"Включить ESP на электрощиток", u8"启用电闸高亮显示");
    ADD_STR("ShowStatusFuseBox", "Show status fusebox", u8"Показать статус электрощитка", u8"显示电闸状态");

    // GhostDesign
    ADD_STR("EnableGhostDesigner", "Enable Ghost Designer", u8"Включить редактор призрака", u8"启用鬼魂信息编辑器");
    ADD_STR("GhostAge", "Ghost Age", u8"Возраст призрака", u8"鬼魂年龄");
    ADD_STR("GhostType", "Ghost Type", u8"Тип призрака", u8"鬼魂类型");
    ADD_STR("IsShy", "Is Shy", u8"Застенчивый призрак", u8"鬼魂是否害羞");
    ADD_STR("EvidenceSettings", "Evidence Settings", u8"Настройки улик", u8"证据设置");
    ADD_STR("EvidenceMode", "Mode", u8"Режим", u8"模式");
    ADD_STR("EvidenceCount", "Evidence Count", u8"Количество улик", u8"证据数量");
    ADD_STR("Evidence", "Evidence", u8"Улика", u8"证据");
    ADD_STR("EvidenceModeRandom", "Random", u8"Случайно", u8"随机");
    ADD_STR("EvidenceModeSelected", "Selected", u8"Выборочно", u8"手动指定证据");

    // GhostESP
    ADD_STR("EnableGhostESP", "Enable Ghost ESP", u8"Включить ESP призрака", u8"启用鬼魂高亮显示");
    ADD_STR("BoxType", "Box Type", u8"Тип рамки", u8"框体类型");
    ADD_STR("BoxThickness", "Box Thickness", u8"Толщина рамки", u8"框体厚度");
    ADD_STR("ShowSkeleton", "Show Skeleton", u8"Показать скелет", u8"显示骨架模型");
    ADD_STR("SkeletonColor", "Skeleton Color", u8"Цвет скелета", u8"骨架颜色");
    ADD_STR("SkeletonThickness", "Skeleton Thickness", u8"Толщина скелета", u8"骨架厚度");
    ADD_STR("ShowPhotoESP", "Show Photo ESP", u8"Показать фото ESP", u8"照片高亮显示");
    ADD_STR("PhotoWidth", "Photo Width", u8"Ширина фото", u8"照片宽度");
    ADD_STR("PhotoHeight", "Photo Height", u8"Высота фото", u8"照片高度");
    ADD_STR("ResetPhotoSize", "Reset Photo Size", u8"Сбросить размер фото", u8"重置照片尺寸");
    ADD_STR("DefaultPhotoSize", "Default: 1.0 x 1.0", u8"По умолчанию: 1.0 x 1.0", u8"默认大小：1.0 * 1.0");
    ADD_STR("PhotoType", "Photo type", u8"Тип фото", u8"照片类型");
    ADD_STR("RefreshImages", "Refresh images", u8"Обновить изображения", u8"刷新图片");
    ADD_STR("NoImagesFound", "No images found", u8"Изображения не найдены", u8"未找到图片");
    ADD_STR("ImagesFolderHint", "Images folder", u8"Папка Images", u8"图片文件夹");
    ADD_STR("ShowBoxESP", "Show box ESP", u8"Показать бокс ESP", u8"显示2D方框");
    ADD_STR("NameColor", "Name color", u8"Цвет имени", u8"鬼魂名称颜色");

    // GhostInter
    ADD_STR("TriggerAbility", "Trigger ability", u8"Активировать способность", u8"触发鬼魂技能");
    ADD_STR("GenericInteraction", "Generic interaction", u8"Общее взаимодействие", u8"触发通用互动");
    ADD_STR("RandomLightSwitch", "Random light switch", u8"Случайное включение света", u8"随机开关灯光");
    ADD_STR("RandomDoorInteraction", "Random door interaction", u8"Случайное взаимодействие с дверью", u8"随机房门互动");
    ADD_STR("RandomPropInteraction", "Random prop interaction", u8"Случайное взаимодействие с предметами", u8"随机物品互动");
    ADD_STR("StandardInteraction", "Standard interaction", u8"Стандартное взаимодействие", u8"触发标准互动");
    ADD_STR("TwinInteraction", "Twin interaction", u8"Взаимодействие с близнецом", u8"触发孪魂互动");

    // GhostMod
    ADD_STR("EnableGhostModifier", "Enable Ghost Modifier", u8"Включить модификацию призрака", u8"启用鬼魂修改器");
    ADD_STR("EnableCustomGhostSpeed", "Enable custom ghost speed", u8"Включить кастомную скорость призрака", u8"启用自定义鬼魂速度");
    ADD_STR("GhostSpeedMod", "Ghost Speed", u8"Скорость призрака", u8"鬼魂速度");
    ADD_STR("ForceAppear", "Force appear", u8"Принудительное появление", u8"强制鬼魂显形");
    ADD_STR("ForcedType", "Forced type", u8"Принудительный тип", u8"请指定鬼魂类型");
    ADD_STR("ForceState", "Force State", u8"Принудительное состояние", u8"强制修改鬼魂状态");
    ADD_STR("FreezeState", "Freeze State", u8"Заморозить состояние", u8"锁定鬼魂状态");
    ADD_STR("SetGhostVisible", "Set ghost visible (only local)", u8"Установить видимость призрака (только локально)", u8"设置鬼魂可见（仅限本机）");

    // Ghost Panel
    ADD_STR("EnableGhostPanel", "Enable Ghost Panel", u8"Включить панель призрака", u8"启用鬼魂信息面板");
    ADD_STR("ShowBansheeTarget", "Show Banshee target (CRASH RISK)", u8"Показывать цель Банши (Риск краша)", u8"显示女妖锁定的目标（有游戏闪退风险）");
    ADD_STR("IsHideSettingsTr", "Hide Settings", u8"Скрыть настройки", u8"隐藏部分鬼魂信息");
    ADD_STR("HideName", "Hide Name", u8"Скрыть имя", u8"隐藏鬼魂名称");
    ADD_STR("HideType", "Hide Type", u8"Скрыть тип", u8"隐藏鬼魂类型");
    ADD_STR("HideAge", "Hide Age", u8"Скрыть возраст", u8"隐藏鬼魂年龄");
    ADD_STR("HideState", "Hide State", u8"Скрыть состояние", u8"隐藏鬼魂状态");
    ADD_STR("HideEvidence", "Hide Evidence", u8"Скрыть улики", u8"隐藏证据类型");
    ADD_STR("HideRoom", "Hide Favorite Room", u8"Скрыть любимую комнату", u8"隐藏鬼魂房间");
    ADD_STR("HideLocation", "Hide Location", u8"Скрыть текущую локацию", u8"隐藏鬼魂当前位置");
    ADD_STR("HideMimicType", "Hide Mimic Type", u8"Скрыть тип мимика", u8"隐藏拟魂模仿的鬼魂类型");
    ADD_STR("HideBansheeTarget", "Hide Banshee Target", u8"Скрыть цель банши", u8"隐藏女妖锁定的目标");
    ADD_STR("FavoriteRoom", "Favorite Room", u8"Любимая комната", u8"鬼魂最喜爱的房间");
    ADD_STR("Location", "Location", u8"Текущая локация", u8"鬼魂位置");
    ADD_STR("MimicType", "Mimic Type", u8"Тип мимика", u8"拟魂模仿的鬼魂类型");
    ADD_STR("BansheeTarget", "Banshee Target", u8"Цель банши", u8"女妖锁定的目标");
    ADD_STR("Evidence", "Evidence", u8"Улики", u8"证据");
    ADD_STR("GhostName", "Ghost Name", u8"Имя призрака", u8"鬼魂名称");
    ADD_STR("GhostType", "Ghost Type", u8"Тип призрака", u8"鬼魂类型");
    ADD_STR("GhostAge", "Ghost Age", u8"Возраст призрака", u8"鬼魂年龄");
    ADD_STR("GhostState", "Ghost State", u8"Состояние призрака", u8"鬼魂状态");

    // SpiritBox Always Answer
    ADD_STR("EnableSpiritBoxAlw", "Enable Spirit Box Always Answer", u8"Включить Spirit Box Always Answer", u8"启用灵盒必定回应");

    // GodMode
    ADD_STR("GodModeEnable", "Enable GodMode", u8"Включить режим бога", u8"启用上帝模式");

    // GrabKey
    ADD_STR("GrabAllKeys", "Grab all keys", u8"Подобрать все ключи", u8"拾取所有钥匙");
    ADD_STR("AutoGrabAllKeys", "Auto grab all keys", u8"Автоматически подобрать все ключи", u8"自动拾取所有钥匙");
    ADD_STR("NoKeysFound", "No keys found.", u8"Ключи не найдены.", u8"未找到钥匙");

    // InfStamina
    ADD_STR("InfinityStaminaEnable", "Enable Infinite Stamina", u8"Включить бесконечную стамину", u8"启用无限体力");

    // LiftButtonSkipAnim
    ADD_STR("VanButtonModifierEnable", "Enable Van button modifier", u8"Включить модификатор кнопки фургона", u8"启用货车按钮修改器");
    ADD_STR("SkipVanAnim", "Enable Skip van animation", u8"Включить пропуск анимации открытия", u8"跳过货车开门动画");
    ADD_STR("AutoOpenVan", "Enable Auto open van", u8"Включить автоматическое открытие фургона", u8"自动开启货车车门");
    ADD_STR("SkipVanButtonDelay", "Enable Skip van button delay", u8"Включить пропуск задержки открытия фургона", u8"跳过货车按钮延迟");

    // NoClip
    ADD_STR("CreditNoClip", "Thanks to Evelien for the NoClip feature!", u8"Спасибо Эвелин за NoClip функцию!", u8"感谢 Evelien 提供的 NoClip 功能！");
    ADD_STR("EnabledNoClip", "Enabled NoClip", u8"Включить NoClip", u8"启用 NoClip 功能");
    ADD_STR("NoClipSpeed", "NoClip speed", u8"NoClip скорость", u8"请设置 NoClip 速度");

    // NotifyInfo
    ADD_STR("EnableNotifyInfo", "Enable Notify Info", u8"Включить уведомления о действиях в игре", u8"启用游戏内通知");
    ADD_STR("GhostTriedHunt", "Ghost tried to hunt.", u8"Призрак попытался начать охоту.", u8"鬼魂试图开启猎杀");
    ADD_STR("GhostStartHunting", "Ghost started hunting!", u8"Призрак начал охоту!", u8"鬼魂开始猎杀！");
    ADD_STR("GhostStopHunting", "Ghost stopped hunting.", u8"Призрак остановил охоту.", u8"鬼魂停止猎杀");
    ADD_STR("BoneCollected", "Bone has been collected.", u8"Косточка была подобрана.", u8"骨头已收集");

    // Pickup
    ADD_STR("EnablePickup", "Enable Pickup", u8"Включить модификацию подбора", u8"启用拾取修改功能");
    ADD_STR("CustomThrow", "Custom throw", u8"Пользовательская сила броска", u8"自定义投掷");
    ADD_STR("ThrowMultiplier", "Throw multiplier", u8"Множитель силы броска", u8"投掷倍率");
    ADD_STR("CustomGrabDistance", "Custom grab distance", u8"Пользовательская дистанция захвата", u8"自定义拾取距离");
    ADD_STR("GrabDistance", "Grab distance", u8"Дистанция захвата", u8"拾取距离");
    ADD_STR("PickupEverything", "Pickup Everything", u8"Поднимать все объекты", u8"拾取所有物品");
    ADD_STR("PocketEverything", "Pocket Everything", u8"Класть всё в карман", u8"把全部物品都装进口袋");

    // PlayerESP
    ADD_STR("EnablePlayerESP", "Enable player ESP", u8"Включить ESP на игроков", u8"启用玩家高亮显示");
    ADD_STR("Show2DBox", "Show 2D box", u8"Показывать 2D коробку", u8"显示2D方框");
    ADD_STR("ShowPlayerSanity", "Show player sanity", u8"Показывать рассудок", u8"显示玩家理智");
    ADD_STR("ShowDeadStatus", "Show dead status", u8"Показывать статус смерти", u8"显示生死状态");
    ADD_STR("ShowCurrentRoom", "Show current room", u8"Показывать текущую комнату", u8"显示当前所在房间");
    ADD_STR("ShowPrestige", "Show prestige", u8"Показывать престиж", u8"显示声望");
    ADD_STR("ShowExperience", "Show experience", u8"Показывать опыт", u8"显示经验");
    ADD_STR("ShowLevel", "Show level", u8"Показывать уровень", u8"显示等级");
    ADD_STR("ShowSprinting", "Show sprinting", u8"Показывать статус бега", u8"显示奔跑状态");
    ADD_STR("ErrorLoadingSettings", "Error loading PlayerESP settings", u8"Ошибка загрузки настроек PlayerESP", u8"加载 PlayerESP 设置时发生错误");

    // PlayerMod
    ADD_STR("Player", "Player", u8"Игрок", u8"玩家");
    ADD_STR("Sanity", "Sanity", u8"Рассудок", u8"理智");
    ADD_STR("Dead", "DEAD", u8"МЁРТВ", u8"死亡");
    ADD_STR("CurrentRoom", "Current room", u8"Текущая комната", u8"当前所在房间");
    ADD_STR("TeleportTo", "Teleport to", u8"Телепорт к", u8"传送");
    ADD_STR("CantTeleportToYourself", "You can't teleport to yourself.", u8"Нельзя телепортироваться к себе", u8"你不能把自己瞬间移动到自己身边");
    ADD_STR("KillPlayer", "Kill player", u8"Убить игрока", u8"杀死玩家");
    ADD_STR("RevivePlayer", "Revive player", u8"Оживить игрока", u8"复活玩家");
    ADD_STR("FreezePlayer", "Freeze player", u8"Заморозить игрока", u8"冻结玩家");
    ADD_STR("UnfreezePlayer", "Unfreeze player", u8"Разморозить игрока", u8"解冻玩家");
    ADD_STR("PlayerAlreadyDead", "Player is already dead.", u8"Игрок уже мёртв", u8"玩家已死亡");
    ADD_STR("PlayerAlreadyAlive", "Player is already revived.", u8"Игрок уже жив", u8"玩家已复活");
    ADD_STR("SanityValue", "Sanity", u8"Рассудок", u8"理智值");
    ADD_STR("SetSanity", "Set sanity", u8"Установить рассудок", u8"设置理智值");

    // PlayerPanel
    ADD_STR("EnablePlayersPanel", "Enable Players Panel", u8"Включить панель игроков", u8"启用玩家信息面板");
    ADD_STR("ShowSanity", "Show Sanity", u8"Показывать рассудок", u8"显示理智");
    ADD_STR("ShowCurrentRoom", "Show Current Room", u8"Показывать текущую комнату", u8"显示当前所在房间");
    ADD_STR("ShowTemperature", "Show Temperature", u8"Показывать температуру", u8"显示温度");
    ADD_STR("ShowLevel", "Show Level", u8"Показывать уровень", u8"显示等级");
    ADD_STR("ShowExperience", "Show Experience", u8"Показывать опыт", u8"显示经验");
    ADD_STR("ShowPrestige", "Show Prestige", u8"Показывать престиж", u8"显示声望");
    ADD_STR("ShowHackerFlag", "Show Hacker Flag", u8"Показывать флаг читера", u8"显示作弊者标记");
    ADD_STR("ShowAverageSanity", "Show Average Sanity", u8"Показывать средний рассудок", u8"显示平均理智值");
    ADD_STR("PlayerSanity", "Sanity", u8"Рассудок", u8"玩家当前理智");
    ADD_STR("PlayerRoom", "Current Room", u8"Текущая комната", u8"玩家所在房间");
    ADD_STR("PlayerTemperature", "Temperature", u8"Температура", u8"温度");
    ADD_STR("PlayerLevel", "Level", u8"Уровень", u8"等级");
    ADD_STR("PlayerExperience", "Experience", u8"Опыт", u8"经验");
    ADD_STR("PlayerPrestige", "Prestige", u8"Престиж", u8"声望");
    ADD_STR("PlayerHacker", "Is Hacker", u8"Читер", u8"是作弊者");
    ADD_STR("AverageSanity", "Average Sanity", u8"Средний рассудок", u8"平均理智值");
    ADD_STR("Yes", "Yes", u8"Да", u8"是");
    ADD_STR("No", "No", u8"Нет", u8"否");
    ADD_STR("You", "You", u8"Вы", u8"你");

    // RewardMod
    ADD_STR("EnableRewardModifier", "Enable Reward Modifier", u8"Включить модификацию наград", u8"启用奖励修改器");
    ADD_STR("AlwaysPerfectGame", "Always Perfect Game", u8"Всегда идеальное расследование", u8"始终保持完美通关");
    ADD_STR("AutoCompleteObjectives", "Auto Complete Objectives", u8"Автоматическое завершение заданий", u8"自动完成任务");
    ADD_STR("CustomInvestigationBonus", "Custom Investigation Bonus", u8"Пользовательский бонус за идеальное расследование", u8"自定义调查奖励");
    ADD_STR("InvestigationBonusValue", "Investigation Bonus Value", u8"Стоимость бонуса за расследование", u8"请设置调查奖励值");
    ADD_STR("CustomMediaBonus", "Custom Media Bonus", u8"Пользовательский бонус за медиа", u8"自定义媒体奖励");
    ADD_STR("MediaBonusValue", "Media Bonus Value", u8"Стоимость медиа-бонуса", u8"请设置媒体奖励值");

    // SaltMod
    ADD_STR("EnableSaltModifier", "Enable Salt Modifier", u8"Включить модификацию соли", u8"启用盐修改器");
    ADD_STR("InfinitySalt", "Infinity Salt", u8"Бесконечная соль", u8"无限盐");
    ADD_STR("GhostNUseSalt", "Ghost doesn't use salt", u8"Призрак не наступает на соль", u8"幽灵不踩盐");
    ADD_STR("ResetAllSalt", "Reset all salt", u8"Обновить всю соль", u8"重置所有盐");
    ADD_STR("UseAllSalt", "Use all salt", u8"Использовать всю соль", u8"使用所有盐");

    // ShopMod
    ADD_STR("EnableShopModifier", "Enable Shop Modifier", u8"Включить модификатор магазина", u8"启用商店修改器");
    ADD_STR("SkipShopTutorials", "Skip Shop Tutorials", u8"Пропустить обучение в магазина", u8"跳过快捷布局教程");
    ADD_STR("CustomCost", "Custom Cost", u8"Своя цена", u8"自定义价格");
    ADD_STR("CustomCostValue", "Custom Cost Value", u8"Значение цены", u8"请设置价格");
    ADD_STR("CustomCount", "Custom Count", u8"Свое количество", u8"自定义数量");
    ADD_STR("CustomCountValue", "Custom Count Value", u8"Значение количества", u8"请设置数量");
    ADD_STR("CustomUpgradeCost", "Custom Upgrade Cost", u8"Своя цена улучшения", u8"自定义升级价格");
    ADD_STR("CustomUpgradeCostValue", "Custom Upgrade Cost Value", u8"Значение цены улучшения", u8"请设置升级价格");
    ADD_STR("CustomRequiredLevel", "Custom Required Level", u8"Свое требуемое уровень", u8"自定义所需等级");
    ADD_STR("CustomRequiredLevelValue", "Custom Required Level Value", u8"Значение требуемого уровня", u8"请设置所需等级");

    // StatsPanel
    ADD_STR("EnableLevelStatsPanel", "Enable Level Stats Panel", u8"Включить панель статистики об контракте", u8"启用等级统计面板");
    ADD_STR("BoneNotFound", "Bone not found.", u8"Кость не найдена.", u8"未找到骨头");
    ADD_STR("BoneCollected", "Bone collected.", u8"Кость была подобрана.", u8"骨头已收集");

    // Teleport
    ADD_STR("Teleport_SavePos", "Save current position", u8"Сохранить текущую позицию", u8"保存当前位置");
    ADD_STR("Teleport_ToSaved", "Teleport to saved point", u8"Телепорт к сохранённой точке", u8"传送到已保存的点位");
    ADD_STR("Teleport_ToCoords", "Teleport to coordinates", u8"Телепорт по координатам", u8"传送到坐标");
    ADD_STR("Teleport_Items", "Items Teleport:", u8"Телепорт предметов:", u8"物品传送：");
    ADD_STR("Teleport_RefreshItems", "Refresh items list", u8"Обновить список предметов", u8"刷新物品列表");
    ADD_STR("Teleport_SelectItem", "Select item to teleport:", u8"Выберите предмет для телепорта", u8"选择要传送的物品：");
    ADD_STR("Teleport_Selected", "Teleport selected", u8"Телепорт выбранного", u8"传送所选物品");
    ADD_STR("Teleport_AllItems", "Teleport all items", u8"Телепортировать все предметы", u8"传送所有物品");
    ADD_STR("Teleport_Bone", "Teleport bone", u8"Телепорт кости", u8"把骨头传送到你的位置");
    ADD_STR("Teleport_Truck", "Teleport to Truck", u8"Телепорт в фургон", u8"传送到货车里");
    ADD_STR("Teleport_Ghost", "Teleport to Ghost", u8"Телепорт к призраку", u8"传送到鬼魂位置");
    ADD_STR("Teleport_Entrance", "Teleport to Entrance", u8"Телепорт к входу", u8"传送到大门入口");
    ADD_STR("TP_ToEntrance", "Teleported to Entrance.", u8"Телепорт к входу.", u8"已传送到大门入口");
    ADD_STR("Teleport_Basement", "Basement", u8"Подвал", u8"地下室");
    ADD_STR("Teleport_LobbyArea", "Lobby area", u8"Лобби", u8"客厅");
    ADD_STR("Teleport_CabinKitchen", "Cabin Kitchen", u8"Кухня домика", u8"小木屋厨房");
    ADD_STR("Teleport_Storage", "Storage", u8"Склад", u8"储藏室");
    ADD_STR("Teleport_MainCorridor", "Main Corridor", u8"Главный коридор", u8"主走廊");
    ADD_STR("Teleport_Attic", "Attic", u8"Чердак", u8"阁楼");
    ADD_STR("Teleport_Bathroom", "Bathroom", u8"Ванная", u8"浴室");
    ADD_STR("Teleport_FoodTent", "Food Tent", u8"Палатка с едой", u8"食品帐篷");
    ADD_STR("Teleport_Chapel", "Chapel", u8"Часовня", u8"教堂");
    ADD_STR("TP_ItemsRefreshed", "Items list refreshed!", u8"Список предметов обновлён!", u8"物品列表已刷新！");
    ADD_STR("TP_NoItems", "No items found.", u8"Предметы не найдены.", u8"未找到物品");
    ADD_STR("TP_ItemTeleported", "Item teleported!", u8"Предмет телепортирован!", u8"物品已传送！");
    ADD_STR("TP_NoSavedPoint", "No saved point found.", u8"Сохранённая точка не найдена.", u8"未找到已保存的点位");
    ADD_STR("TP_PosSaved", "Saved current position!", u8"Текущая позиция сохранена!", u8"当前点位已保存");
    ADD_STR("TP_ToSaved", "Teleported to saved point!", u8"Телепорт к сохранённой точке.", u8"已传送到保存的点位！");
    ADD_STR("TP_ToTruck", "Teleported to Truck.", u8"Телепорт в фургон.", u8"已传送到货车里");
    ADD_STR("TP_ToGhost", "Teleported to Ghost.", u8"Телепорт к призраку.", u8"已传送到鬼魂位置");
    ADD_STR("TP_BoneTeleported", "Bone teleported!", u8"Кость телепортирована.", u8"骨头已传送！");
    ADD_STR("TP_LocalPlayerMissing", "Local player not found.", u8"Локальный игрок не найден.", u8"未找到本地玩家");
    ADD_STR("TP_TruckNotFound", "Truck not found.", u8"Фургон не найден.", u8"未找到货车");

    // Watermark
    ADD_STR("EnableWatermark", "Enable Watermark", u8"Включить водяной знак", u8"启用水印");
    ADD_STR("Watermark_ShowFPS", "Show FPS", u8"Показывать FPS", u8"显示帧率");
    ADD_STR("Watermark_ShowSanity", "Show average sanity", u8"Показывать среднюю рассудочность", u8"显示平均理智值");
    ADD_STR("Watermark_ShowPing", "Show ping", u8"Показывать пинг", u8"显示延迟");

    // Temperature Panel
    ADD_STR("TemperaturePanelEnable", "Enable temperature panel", u8"Включить панель температуры", u8"启用温度面板");

    // Fast Thermometer
    ADD_STR("FastThermometerEnable", "Enable fast thermometer", u8"Включить быстрый термометр", u8"启用快速温度计");
    ADD_STR("FastThermometerInfo", "It only works for the second and third tiers", u8"Это работает только для второго и третьего тира", u8"此功能仅适用于第2和第3级温度计");

    // No End Game
    ADD_STR("EnableNoEndGame", "Enable no end game", u8"Включить бесконечную игру (No end game)", u8"启用禁止自动结束游戏功能");

    // Crosshair Modifier
    ADD_STR("CrosshairModifierEnable", "Enable Crosshair Modifier", u8"Включить модификацию прицела", u8"启用准星修改器");
    ADD_STR("Apply", "Apply", u8"Применить", u8"应用");
    ADD_STR("RGBModeTr", "RGB Mode", u8"RGB Режим", u8"开启 RGB 模式");
    ADD_STR("CrosshairSizeTr", "Crosshair size", u8"Размер прицела", u8"准星大小");

    // Potatoe ESP Fun
    ADD_STR("PotatoeESPEn", "Enable Potatoe ESP (FuN)", u8"Включить ESP на картофель (FuN)", u8"启用土豆高亮显示（娱乐功能）");

    // Flashlight Modifier
    ADD_STR("FlashlightModifierEnable", "Enable flashlight modifier", u8"Включить модификацию фонарика", u8"启用手电筒修改器");
    ADD_STR("NoFlashlightFlicker", "No flashlight flicker", u8"Отключить мерцание фонарика", u8"阻止鬼魂猎杀时的手电筒闪烁");
    ADD_STR("DisableDifficultyCheck", "Disable the difficulty check", u8"Отключить проверку сложности", u8"禁用难度限制检查");

    // Always bloodmoon
    ADD_STR("AlwaysBloodmoonEnable", "Enable always bloodmoon", u8"Включить всегда кровавую луну", u8"启用始终血月天气");

    // Auto Pickup Bone
    ADD_STR("AutoPickupBoneEnable", "Enable auto pickup bone", u8"Включить автоматический подбор кости", u8"启用自动拾取骨头");

    // Photo Modifier
    ADD_STR("PhotoModifierEnable", "Enable photo modifier", u8"Включить модификацию фотографий", u8"启用照片修改器");
    ADD_STR("X5Photo", "x5 Photo", u8"x5 Фотографии", u8"5倍照片奖励");
    ADD_STR("AutoPhoto", "Auto photo ghost", u8"Автоматические фотографии призрака", u8"自动拍鬼魂照片");
    ADD_STR("NoDelayPhoto", "No delay between photos", u8"Нет задержки между фотографиями", u8"拍照时无冷却延迟");
    ADD_STR("SkipAnimationPhoto", "Skip photo animation", u8"Пропустить анимацию фотографирования", u8"跳过拍照动画");
	ADD_STR("GhostPhotoTaken", "Ghost photo taken!", u8"Сделана фотография призрака!", u8"已成功拍摄鬼魂照片！");

    // Font Changer
	ADD_STR("EnableFontChanger", "Enable font changer", u8"Включить смену шрифта", u8"启用字体修改器");

    // Journal Modifer
    ADD_STR("EnableJournalModifier", "Enable journal modifier", u8"Включить модификацию журнала", u8"启用日志修改器");
    ADD_STR("OldGhostButtonPosition", "Old ghost button positions", u8"Старые позиции кнопок призраков", u8"恢复旧版鬼魂按钮布局");
    ADD_STR("AutoSelectGhost", "Auto select ghost", u8"Автоматический выбор призрака", u8"自动选择鬼魂");
    ADD_STR("CorrectGhostAlwaysFirst", "Correct ghost always first", u8"Правильный призрак всегда первый", u8"让正确的鬼魂类型始终排在列表第一位");

    // Jackalope ESP
    ADD_STR("EnableJackalopeESP", "Enable Jackalope ESP", u8"Включить ESP на шакалоп", u8"启用鹿角兔高亮显示");

    // AutoGame
    ADD_STR("EnableAutoGame", "Enable Auto Game", u8"Включить автоматическую игру", u8"启用自动游戏");
    ADD_STR("AutoGameDelay", "Auto Game Delay", u8"Задержка автоматической игры", u8"自动游戏延迟");
    ADD_STR("AutoGameRunning", "AutoGame is running.\nStopping is temporarily unavailable to ensure safe completion of the current cycle.\nPlease use the \"Stop\" button in the AutoGame panel to request a safe shutdown.", u8"Автоигра запущена.\nОстановка временно недоступна для обеспечения безопасного завершения текущего цикла.\nПожалуйста, используйте кнопку \"Стоп\" на панели автоигры, чтобы запросить безопасное завершение игры.", u8"自动游戏功能正在运行\n为确保当前循环安全结束，此功能暂时无法停止\n请使用自动游戏面板中的“停止”按钮来安全关闭");
    
    // FuseBox Modifier
    ADD_STR("EnableFuseBoxModifier", "Enable fusebox modifier", u8"Включить модификатор электрощитка", u8"启用电闸修改功能");
    ADD_STR("AutoOnFuse", "Auto On Fuse", u8"Автоматическое включение электрощитка", u8"自动开启电闸");
    ADD_STR("FuseBoxOnByCheat", "FuseBox on by cheat.", u8"Электрощиток включён с помощью чита.", u8"电闸已由修改器强制开启");

    // Show Micro
    ADD_STR("ShowMicroEnable", "Show Microphone", u8"Показать микрофон", u8"显示麦克风");
    ADD_STR("MicroScale", "Microphone scale", u8"Размер микрофона", u8"麦克风大小");
    ADD_STR("MicroOnColor", "Microphone On Color", u8"Цвет включенного микрофона", u8"麦克风开启时的颜色");

    // Cosmetics Unlocker
    ADD_STR("CosmeticUnlockerEnable", "Enable cosmetic unlocker", u8"Включить разблокировку косметики", u8"启用外观解锁功能");
    ADD_STR("CosmeticWarning", "Warning! We are not responsible for the subsequent ban when using this feature.\nUse it at your own risk. Although a ban is unlikely.", u8"Внимание! Мы не несем ответственности за последующий бан при использовании этой функции.\nИспользуйте ее на свой страх и риск. Хотя бан маловероятен.", u8"警告！我们不对使用此功能可能导致的封号负责\n请自行承担使用风险，尽管被封号的可能性极低");
    ADD_STR("CosmeticCredits", "Created by code PhasmoUnlocker", u8"Создано с помощью кода PhasmoUnlocker", u8"基于 PhasmoUnlocker 代码制作");

    // Music Panel
    ADD_STR("MusicPanelEnable", "Enable music panel", u8"Включить музыкальную панель", u8"启用音乐面板");
    ADD_STR("ShowOnlyMenu", "Show only in menu", u8"Показывать только в меню", u8"仅在菜单中显示");

    // Audio Modifier
    ADD_STR("AudioModifierEnable", "Enable audio modifier", u8"Включить модификатор аудио", u8"启用音频修改功能");
    ADD_STR("DisableWeatherAudio", "Disable weather audio", u8"Выключить аудио погоды", u8"禁用天气音效");

    // Skip player animation
	ADD_STR("SkipPlayerAnimEnable", "Enable skip player animation", u8"Включить пропуск анимации игрока", u8"启用跳过玩家动画");

    // Headers
    ADD_STR("ActivityMonitor_Header", "Activity Monitor", u8"Монитор активности", u8"活动强度监视器");
    ADD_STR("AlwaysBloodMoon_Header", "Always BloodMoon", u8"Всегда кровавая луна", u8"始终保持血月天气");
    ADD_STR("AntiKick_Header", "AntiKick", u8"Антикик", u8"反踢出");
    ADD_STR("Autopickupbone_Header", "Auto pickup bone", u8"Автоматический подбор кости", u8"自动拾取骨头");
    ADD_STR("CrosshairModifier_Header", "Crosshair Modifier", u8"Модификатор прицела", u8"准星修改器");
    ADD_STR("CursedItemsControll_Header", "CursedItems Controll", u8"Управление проклятыми предметами", u8"诅咒道具控制");
    ADD_STR("CustomLookLimits_Header", "Custom Look Limits", u8"Пользовательские ограничения обзора", u8"视角限制修改");
    ADD_STR("CustomSpeed_Header", "Custom Speed", u8"Пользовательская скорость", u8"自定义速度");
    ADD_STR("Customname_Header", "Custom name", u8"Пользовательское имя", u8"自定义名称");
    ADD_STR("DifficultyModifier_Header", "Difficulty Modifier", u8"Модификатор сложности", u8"难度修改器");
    ADD_STR("DoorModifier_Header", "Door Modifier", u8"Модификатор дверей", u8"门修改器");
    ADD_STR("EvidenceESP_Header", "Evidence ESP", u8"ESP доказательств", u8"证据高亮显示");
    ADD_STR("ExitVanSolo(host)_Header", "Exit Van Solo (host)", u8"Выход из фургона в одиночку (хост)", u8"单人上车离开（仅限房主可用）");
    ADD_STR("FastThermometer_Header", "Fast Thermometer", u8"Быстрый термометр", u8"快速温度计");
    ADD_STR("FlashlightModifier_Header", "Flashlight Modifier", u8"Модификатор фонарика", u8"手电筒修改器");
    ADD_STR("FoVEditor_Header", "FoVEditor", u8"Редактор FoV", u8"视野编辑器");
    ADD_STR("FontChanger_Header", "Font Changer", u8"Смена шрифта игры", u8"字体修改器");
    ADD_STR("ForceStart_Header", "Force Start", u8"Принудительный старт", u8"强制开始");
    ADD_STR("Fullbright_Header", "Fullbright", u8"Полная яркость", u8"高亮模式");
    ADD_STR("FuseBoxESP_Header", "FuseBox ESP", u8"ESP на предохранители", u8"电闸高亮显示");
    ADD_STR("GhostDesigner(HOST)_Header", "Ghost Designer (HOST)", u8"Дизайнер призраков (ХОСТ)", u8"鬼魂编辑器（仅限房主可用）");
    ADD_STR("GhostESP_Header", "Ghost ESP", u8"ESP на призраков", u8"鬼魂高亮显示");
    ADD_STR("GhostInteractionControl_Header", "Ghost Interaction Control", u8"Управление взаимодействиями призрака", u8"鬼魂互动控制");
    ADD_STR("GhostModifier_Header", "Ghost Modifier", u8"Модификатор призрака", u8"鬼魂修改器");
    ADD_STR("GhostPanel_Header", "Ghost Panel", u8"Панель призрака", u8"鬼魂信息面板");
    ADD_STR("GodMode_Header", "GodMode", u8"Режим бога", u8"上帝模式");
    ADD_STR("GrabKeys_Header", "Grab Keys", u8"Поднять ключи", u8"拾取钥匙");
    ADD_STR("InfinityStamina_Header", "Infinity Stamina", u8"Бесконечная выносливость", u8"无限体力");
    ADD_STR("JackalopeESP_Header", "Jackalope ESP", u8"ESP на шакалоп", u8"鹿角兔高亮显示");
    ADD_STR("JournalModifier_Header", "Journal Modifier", u8"Модификатор журнала", u8"日志修改器");
    ADD_STR("LevelStatsPanel_Header", "LevelStats Panel", u8"Панель статистики уровня", u8"等级统计面板");
    ADD_STR("MapModifier_Header", "Map Modifier", u8"Модификатор карты", u8"地图修改器");
    ADD_STR("NoClip_Header", "NoClip", u8"Ноуклип", u8"穿墙模式（NoClip）");
    ADD_STR("NoEndGame_Header", "No End Game", u8"Отсутствие конца игры", u8"禁止自动结束游戏");
    ADD_STR("NotifyInfo_Header", "Notify Info", u8"Информация уведомлений", u8"通知信息");
    ADD_STR("PhotoModifier_Header", "Photo Modifier", u8"Модификатор фотографий", u8"照片修改器");
    ADD_STR("Pickup_Header", "Pickup", u8"Поднять предмет", u8"拾取项修改");
    ADD_STR("PlayerESP_Header", "Player ESP", u8"ESP на игроков", u8"玩家高亮显示");
    ADD_STR("PlayerModifier_Header", "Player Modifier", u8"Модификатор игрока", u8"玩家修改器");
    ADD_STR("PlayersPanel_Header", "Players Panel", u8"Панель игроков", u8"玩家信息面板");
    ADD_STR("PotatoeESP_Header", "Potatoe ESP", u8"ESP на картошку", u8"土豆高亮显示");
    ADD_STR("RewardModifier_Header", "Reward Modifier", u8"Модификатор наград", u8"奖励修改器");
    ADD_STR("SaltModifier(ONLYYOU)_Header", "Salt Modifier (ONLY YOU)", u8"Модификатор соли (ТОЛЬКО ВЫ)", u8"盐修改器（仅对本机生效）");
    ADD_STR("ShopModifier_Header", "Shop Modifier", u8"Модификатор магазина", u8"商店修改器");
    ADD_STR("SpiritBoxAlwaysAnswer_Header", "Spirit Box Always Answer", u8"Spirit Box Always Answer", u8"通灵盒始终有回应");
    ADD_STR("Teleport_Header", "Teleport", u8"Телепортация", u8"传送功能");
    ADD_STR("TemperaturePanel_Header", "Temperature Panel", u8"Панель температуры", u8"温度面板");
    ADD_STR("VanButtonModifier_Header", "Van Button Modifier", u8"Модификатор кнопки фургона", u8"货车按钮修改器");
    ADD_STR("Watermark_Header", "Watermark", u8"Водяной знак", u8"水印设置");
    ADD_STR("FuseBoxModifier_Header", "FuseBox Modifier", u8"Модификатор электрощитка", u8"电闸修改器");
    ADD_STR("AutoGame_Header", "Auto Game", u8"Автоматическая игра", u8"自动游戏");
    ADD_STR("ShowMicro_Header", "Show Microphone", u8"Показать микрофон", u8"显示麦克风");
    ADD_STR("CosmeticUnlocker_Header", "Cosmetic Unlocker", u8"Разблокировщик косметики", u8"外观解锁器");
    ADD_STR("MusicPanel_Header", "Music Panel", u8"Музыкальная панель", u8"音乐面板");
    ADD_STR("PlayerDeath_GodModePrevented", "Player death prevented by GodMode. Reason death: ", u8"Смерть игрока предотвращена режимом бога. Причина смерти: ", u8"上帝模式已阻止玩家死亡，致死原因：");
    ADD_STR("AudioModifier_Header", "Audio Modifier", u8"Модификатор аудио", u8"音频修改器");
    ADD_STR("SkipLayerAnimation", "Skip player animations", u8"Пропустить анимации игрока", u8"跳过玩家动画");

    // Template
    ADD_STR("", "", u8"");
}