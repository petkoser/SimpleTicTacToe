# SimpleTicTacToe

SmipleTicTacToe - это крестики-нолики для двух игроков, написанная Qt/Qml/C++. 
Основная логика игры реализована в классе GameController, в том числе: 
выполняется проверка допустимых ходов, определяется победитель или принимается
решение о ничьей, ведется подсчет выигранных раундов. Выбор игрока, который будет 
ходить первым, случаен для каждого раунда. 
Для начала игры необходимо нажать на кнопку "New game", завершение игры происходит 
автоматически, когда любой из игроков побеждает в 2 раундах. Для начала следующего 
раунда нажать на кнопку "Next round". 

Дополнительно добавлена возможность указать имена игроков. Имена игроков не должны 
совпадать. Дополнительно добавлена возможность получения статистики по играм в классе 
Game History (в Qml сейчас отображается статистика по всем играм между текущими 
игроками в поле "Game score"), статистика обновляется при изменении имен игроков. 


SmipleTicTacToe is a two-player tic-tac-toe game written in Qt/Qml/C++. The main 
logic of the game is implemented in the GameController class, including: valid moves 
are checked, the winner is determined or a draw is decided, and the rounds won are 
counted. The choice of the player who will go first is random for each round. 
To start the game, you need to click on the "New game" button, the game ends 
automatically when any of the players wins 2 rounds. To start the next round, 
click on the "Next round" button. 

Additionally, the ability to specify the names of the players has been added. 
The names of the players must not match. Additionally, the ability to get 
statistics on games in the Game History class has been added (Qml now displays 
statistics on all games between current players in the "Game score" field), 
statistics are updated when player names change.
