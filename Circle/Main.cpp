#include "Player.h"
#include "Enemy.h"
#include "GlobalRes.h"

int main()
{
	srand(time(NULL));

	//Resources
	int mode = 0;
	GlobalRes res;
	Clock clock;
	//Resources

	//Loading
	vector<Texture> loadTexture;
	Sprite loadSprite;
	double frameTime = 0;
	int loadCntFrame = 16, curLoadFrame = 0;
	loadTexture.resize(loadCntFrame);
	string link = "textures/48pix/load_A.png";
	for (int i = 0; i < loadCntFrame; i++)
	{
		loadTexture[i].loadFromFile(link);
		link[20]++;
	}
	int toload = 0;
	//Loading

	res.loadMap("maps/map_menu.txt", "textures/48pix/map.png");
	res.blockSize = 48;
	res.resolution = make_pair(24 * res.blockSize, 14 * res.blockSize);
	RenderWindow window(VideoMode(res.resolution.first, res.resolution.second), "Game", Style::Close);
	//window.setVerticalSyncEnabled(1);

	Player player(FloatRect(2 * res.blockSize, 3 * res.blockSize, res.blockSize, res.blockSize), "textures/48pix/player_1.png", 22, 9);
	Enemy enemy(FloatRect(5 * res.blockSize, 7 * res.blockSize, res.blockSize, res.blockSize), "textures/48pix/enemy.png", NULL, 1);
	enemy.dx = 0.05;
	Enemy unit_menu_1(FloatRect(1 * res.blockSize, 10 * res.blockSize, res.blockSize, res.blockSize), "textures/48pix/player_1.png", 22, 9);
	Enemy unit_menu_2(FloatRect(1 * res.blockSize, 12 * res.blockSize, res.blockSize, res.blockSize), "textures/48pix/player_1.png", 22, 9);
	unit_menu_2.dx = 0.05;
	Enemy unit_menu_3(FloatRect(9 * res.blockSize, 8 * res.blockSize, res.blockSize, res.blockSize), "textures/48pix/player_1.png", 22, 9);
	Enemy unit_menu_4(FloatRect(5 * res.blockSize, 7 * res.blockSize, res.blockSize, res.blockSize), "textures/48pix/player_1.png", 22, 9);
	Enemy unit_menu_5(FloatRect(7 * res.blockSize, 2 * res.blockSize, res.blockSize, res.blockSize), "textures/48pix/player_1.png", 22, 9);
	unit_menu_3.sprite.setColor(Color::Red);
	unit_menu_4.sprite.setColor(Color::Red);
	unit_menu_5.sprite.setColor(Color::Red);

	//Menu
	Texture menu_1, menu_2, menu_3;
	menu_1.loadFromFile("textures/new_game.png");
	menu_2.loadFromFile("textures/levels.png");
	menu_3.loadFromFile("textures/exit.png");
	Sprite new_game(menu_1), levels(menu_2), exit(menu_3);
	new_game.setPosition(res.resolution.first * 4 / 5 - new_game.getLocalBounds().width / 2, 40);
	levels.setPosition(res.resolution.first * 4 / 5 - new_game.getLocalBounds().width / 2, 255);
	exit.setPosition(res.resolution.first * 4 / 5 - new_game.getLocalBounds().width / 2, 470);
	int MenuNum = 0;

	//Pause
	Texture menu_4, menu_5, menu_6;
	menu_4.loadFromFile("textures/resume.png");
	menu_5.loadFromFile("textures/return_to_main.png");
	menu_6.loadFromFile("textures/leave.png");
	Sprite resume(menu_4), return_to_main(menu_5), leave(menu_6);
	int PauseNum = 0;

	while (window.isOpen())
	{

		res.time = clock.restart().asMicroseconds();
		res.time /= 600;

		if (mode == 0) //Main menu
		{

			unit_menu_1.update(res);
			if (unit_menu_1.onGround)
				unit_menu_1.dy = -0.45;
			unit_menu_2.update(res);
			unit_menu_3.update(res);
			unit_menu_4.update(res);
			unit_menu_5.update(res);

			new_game.setColor(Color::White);
			levels.setColor(Color::White);
			exit.setColor(Color::White);
			MenuNum = 0;
			if (IntRect(new_game.getGlobalBounds()).contains(Mouse::getPosition(window)))
			{
				new_game.setColor(Color(35, 165, 220, 255));
				MenuNum = 1;
			}
			if (IntRect(levels.getGlobalBounds()).contains(Mouse::getPosition(window)))
			{
				levels.setColor(Color(35, 165, 220, 255));
				MenuNum = 2;
			}
			if (IntRect(exit.getGlobalBounds()).contains(Mouse::getPosition(window)))
			{
				exit.setColor(Color(35, 165, 220, 255));
				MenuNum = 3;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (MenuNum == 1)
				{
					mode = 2;
					toload = 1;
					res.loadMap("maps/map_3.txt", "textures/48pix/map.png");
					//res.time = 0;
					continue;
				}
				if (MenuNum == 2)
				{
					//while (!Keyboard::isKeyPressed(Keyboard::Escape));
				}
				if (MenuNum == 3)
				{
					window.close();
				}
			}
			window.clear(Color::White);

			res.displayMap(window);
			window.draw(unit_menu_1.sprite);
			window.draw(unit_menu_2.sprite);
			window.draw(unit_menu_3.sprite);
			window.draw(unit_menu_4.sprite);
			window.draw(unit_menu_5.sprite);
			window.draw(new_game);
			window.draw(levels);
			window.draw(exit);

			window.display();
		}

		if (mode == 1) //Game
		{
			if (Keyboard::isKeyPressed(Keyboard::Num1))
			{
				player.sprite.setColor(Color::White);
				player.typeNum = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Num2))
			{
				player.sprite.setColor(Color::Red);
				player.typeNum = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Num3))
			{
				player.sprite.setColor(Color::Magenta);
				player.typeNum = 2;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				resume.setPosition(res.resolution.first * (rand() % 4 + 1) / 5 - new_game.getLocalBounds().width / 2, 40);
				return_to_main.setPosition(res.resolution.first * (rand() % 4 + 1) / 5 - new_game.getLocalBounds().width / 2, 255);
				leave.setPosition(res.resolution.first * (rand() % 4 + 1) / 5 - new_game.getLocalBounds().width / 2, 470);
				mode = 2;
				toload = 3;
			}
			player.update(res);
			if (player.position.left + player.position.width / 2 > res.resolution.first / 2 && res.W * res.blockSize - player.position.left - player.position.width / 2 > res.resolution.first / 2)
				res.offsetX = player.position.left - res.resolution.first / 2 + player.position.width / 2;
			if (player.position.top + player.position.height / 2 > res.resolution.second / 2 && res.H * res.blockSize - player.position.top - player.position.height / 2 > res.resolution.second / 2)
				res.offsetY = player.position.top - res.resolution.second / 2 + player.position.height / 2;

			enemy.update(res);
			if (enemy.life && player.position.intersects(enemy.position))
			{
				if (player.dy > 0.2)
				{
					player.dy = -0.3;
					enemy.life = 0;
				}
				else
				{
					player.sprite.setColor(Color::Black);
				}
			}

			window.clear(Color::White);

			res.displayMap(window);
			window.draw(player.sprite);
			if (res.onScreen(enemy.sprite))
				window.draw(enemy.sprite);

			window.display();
		}

		if (mode == 2) //Loading
		{
			frameTime += res.time;
			if (frameTime > 125)
			{
				frameTime = 0;
				curLoadFrame++;
				if (curLoadFrame >= loadCntFrame)
				{
					mode = toload;
					curLoadFrame = 0;
					window.clear();
					continue;
				}
				loadSprite.setTexture(loadTexture[curLoadFrame]);
				for (int i = 0; i < 14; i++)
				{
					for (int j = 0; j < 24; j++)
					{
						loadSprite.setPosition(j * res.blockSize, i * res.blockSize);
						window.draw(loadSprite);
					}
				}
				window.display();
			}
		}

		if (mode == 3) //Pause
		{

			resume.setColor(Color::White);
			return_to_main.setColor(Color::White);
			leave.setColor(Color::White);
			PauseNum = 0;
			if (IntRect(resume.getGlobalBounds()).contains(Mouse::getPosition(window)))
			{
				resume.setColor(Color(35, 165, 220, 255));
				PauseNum = 1;
			}
			if (IntRect(return_to_main.getGlobalBounds()).contains(Mouse::getPosition(window)))
			{
				return_to_main.setColor(Color(35, 165, 220, 255));
				PauseNum = 2;
			}
			if (IntRect(leave.getGlobalBounds()).contains(Mouse::getPosition(window)))
			{
				leave.setColor(Color(35, 165, 220, 255));
				PauseNum = 3;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (PauseNum == 1)
				{
					mode = 2;
					toload = 1;
					//res.loadMap("maps/map_3.txt", "textures/48pix/map.png");
					//res.time = 0;
					continue;
				}
				if (PauseNum == 2)
				{
					mode = 2;
					toload = 0;
					res.loadMap("maps/map_menu.txt", "textures/48pix/map.png");
					res.offsetX = res.offsetY = 0;
					//while (!Keyboard::isKeyPressed(Keyboard::Escape));
				}
				if (PauseNum == 3)
				{
					window.close();
				}
			}

			window.draw(resume);
			window.draw(return_to_main);
			window.draw(leave);

			window.display();
		}
		
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();
	}

	return 0;
}