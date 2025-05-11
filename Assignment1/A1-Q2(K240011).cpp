#include <iostream>
#include <string>

using namespace std;


class Ball {
public:
    int x, y;
    Ball() : x(0), y(0) {}
    int getX() { return x; }
    int getY() { return y; }
    void move(int dx, int dy) { x += dx; y += dy; }
    pair<int, int> getPosition() { return {x, y}; }
};


class Goal {
public:
    int x, y;
    Goal() : x(3), y(3) {}
    bool isGoalReached(int ballX, int ballY) { return (ballX == x && ballY == y); }
};


class Robot {
public:
    string name;
    int hits;
    Robot(string n) : name(n), hits(0) {}
    void hitBall(Ball &ball, string direction) {
        if (direction == "up") ball.move(0, 1);
        else if (direction == "down") ball.move(0, -1);
        else if (direction == "left") ball.move(-1, 0);
        else if (direction == "right") ball.move(1, 0);
        hits++;
    }
};


class Team {
public:
    string teamName;
    Robot *robot;
    Team(string name, string robotName) {
        teamName = name;
        robot = new Robot(robotName);
    }
};


class Game {
public:
    Team *teamOne;
    Team *teamTwo;
    Ball ball;
    Goal goal;
    
    Game() {
        teamOne = new Team("Team A", "Robot A");
        teamTwo = new Team("Team B", "Robot B");
    }
    
    void play(Team *team) {
        while (!goal.isGoalReached(ball.getX(), ball.getY())) {
            team->robot->hitBall(ball, "right");
        }
    }
    
    void declareWinner() {
        if (teamOne->robot->hits < teamTwo->robot->hits)
            cout << teamOne->teamName << " wins!" << endl;
        else
            cout << teamTwo->teamName << " wins!" << endl;
    }
    
    void startGame() {
        play(teamOne);
        play(teamTwo);
        declareWinner();
    }
};


int main() {
	
    cout << "Name: Syed Nadir Shah" << endl;
    cout << "Student ID: K240011" << endl;
    
    Game game;
    game.startGame();
    
    return 0;
}

