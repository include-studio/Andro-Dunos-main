# Changelog


All notable changes to this project will be documented in this file.


## [Unreleased]


## [0.7.0] - 2018-05-17


### Summarized

- Shield and enemies in stage 4 added.

### Extended


#### Added


- Created Enemy_GreenMiniShip .cpp and .h .

- Created Enemy_TinyRedShip .cpp and .h .

- ModuleShieldPlayer1 .cpp and .h .

- ModuleShieldPlayer2 .cpp and .h .

- Wall crashing in Stage4.cpp and .h .

- Created Enemy_Column .cpp and .h .

- New paths in Enemy_WavingShip.cpp and .h . 

- Freeze camera in ModuleRender .cpp .h .

- Second shoot in Enemy_MiniMiniBoss .cpp and .h .

- New path Enemy_HoritzontalRocket .cpp and .h .


#### Fixed


- Respawn of players.

- StageClear fades.

- Bonus animation.

- OneUp rebound.

- God Mode when respawn.

- Enemies can respawn in stage4.

- Animation player with controller.

- Players can't collide.

- Buttons structure updated.

- Hp, score and power up don't reset when fading.


## [0.6.0] - 2018-05-11


### Summarized

- Stage 4 implemented almost entirely,controllers fixed.

### Extended


#### Added


- Collision map stage 4

- Audio stage 4.

- Water animation in stage 4.

- Heal debugging mode.

- InsertCoin/press2pbutton logic.


#### Fixed


- Stage 4 scroll fixed with background.

- Joysticks fixed.

- Now when coin is introduced it enters to the main menu.

- Stageclear fixed.

- DPadUp Controller (insert coin) fixed.


## [0.5.3] - 2018-05-07


### Summarized

- Stage 4 implemented minimally, controllers added with errors and some UI/bonus upgrades. Also Fullscreen is implemented.

### Extended


#### Added


- Added Controller inputs in ModuleInput.

- Added GameOver, Press1P/2PButton animations in ModuleUI.

- Created ModuleStage4 .cpp and .h .

- Added one_up in PowerUp .cpp and .h.

- Added Fullscreen in ModuleWindow.


#### Fixed


- Respawn player 2 fixed.


## [0.5.2.1] - 2018-04-22


### Summarized

- New enemy, audio fixed and bonuses have a path.

### Extended


#### Added


#### Fixed


- Coins fixed when played 2 is enabled.

- Respawn fixed player 1 and 2.


## [0.5.1] - 2018-04-22


### Summarized

- New enemy, audio fixed and bonuses have a path.

### Extended


#### Added


- Created MiniMiniBoss .cpp and .h .


#### Fixed


- AudioFx modified (now it unloads).

- Now both bonuses have a path.

- Music now fades in and out.

- Credits can't go less than 0.


## [0.5.0] - 2018-04-22


### Summarized

- UI improvements, some bug fixes and power ups.

### Extended


#### Added


-Added HP and Credits.

-Added 2nd player score.

-Created ModuleSubMainMenu .cpp and .h .

-Created ModulePowerUp .cpp and .h .


#### Fixed


- Score and highscore.

- Laser 1 particle.


#### Eliminated


- Some .dll in Game folder.

- Stage 2.



## [0.4.6] - 2018-04-20


### Summarized

-Added UI, more enemies and fonts.

### Extended


-Added all collision boxes of stage1.

-Upgraded Camera funcionality.

-God mode player 1 and 2 has linked.

-Some explosions added.

-Score system added.



## [0.4.5] - 2018-04-18


### Summarized

-Added enemies, explosions and collision boxes. Also new animation in stage clear.

### Extended


#### Added


- Created ModuleEnemies.cpp and .h .

- Created Enemies.cpp and .h .

- Created Enemy_WavingShip.cpp and .h .

- Score box in stageclear.

- Mini Explosion animated.


## [0.4.0] - 2018-04-16


### Summarized

-Collisions, camera limits, god mode and module audio improved.

### Extended


#### Added


- Created Collisions .cpp and .h .

- Camera Limits struct.

- God Mode, player doesnt collide.


#### Fixed

- Module Audio play fx sounds fixed.


## [0.3.0] - 2018-04-13


### Summarized

- NeoGeo, ViscoGame and MainMenu scenes are done. StageClear and GameOver too.

- Players can shoot.

### Extended


#### Added


- Created ModuleNeoGeo .cpp and .h .

- Created ModuleViscoGames.cpp and .h .

- Created ModuleGameOver.cpp and .h .

- Created ModuleStageClear. cpp and .h .

- Created ModuleParticles. cpp and .h .

#### Fixed


- Stars

- ModuleAudio init errors with SDL_Mixer.

- StageClear animations.

- MainMenu animations.

- Stage 1 ground is visible in smaller computers.


## [0.2.1] - 2018-04-08


### Summarized

- Added sound.

- Animations' bug fixed.

- Second player is able.

- Added Main Menu, Stage 2 and Stage clear scenes.

- Fades between the stages.

### Extended


#### Added


- Created ModuleFadeToBlack .cpp and .h .

- Created ModuleMainMenu .cpp and .h .

- Created ModulePlayer2 .cpp and .h .

- Created ModuleStageClear. cpp and .h .


#### Fixed


- Animation of the ship

- ModuleAudio


#### Changed

- Changed ModulePlayer to ModulePlayer1.

- Changed ModuleBackground to ModuleStage1.


## [0.2.0] - 2018-04-05


### Summarized

- Created the player ship and its movements with inputs.

- Added all background (stars, planets, ground, ...) with different scrolls .

### Extended


#### Added



- Created Animation.h .

- Created p2Point.h .

- Created ModuleBackground .cpp and .h .

- Created ModulePlayer. cpp and .h .


## [0.1.0] - 2018-03-22


### Summarized

- Created the base of the code.

- Added background and scroll.

### Extended


#### Added



- Uploaded SDL_AndroDunos in Github.

- Added SDL libraries (main, audio, mixer).

- Added background.

- Created Application .cpp and .h .

- Created Globals .cpp and .h .

- Created ModuleAudio.cpp and .h .

- Created ModuleInput .cpp and .h .

- Created ModuleRender.cpp and .h .

- Created ModuleTextures .cpp and .h .

- Created ModuleWindow .cpp and .h .

- Created log.cpp .

- Created Main.cpp .

- Created MemLeaks.cpp .

- Created Module.h .