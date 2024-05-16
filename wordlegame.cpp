#include "wordlegame.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTime>

WordleGame::WordleGame(QObject *parent) : QObject(parent)
{
    loadWordsFromFile(":/Sources/words.txt", validWords);
    loadWordsFromFile(":/Sources/valid_guesses.txt", validGuesses);

    gameOver = false;
    targetWord = selectTargetWord(validWords);
}

QString WordleGame::selectTargetWord(const QStringList& words)
{
    srand(QTime::currentTime().msec()); // qsrand changed to srand while migrating 5.14 - 6.7
    int index = rand() % words.size(); // qrand changed to rand while migrating 5.14 - 6.7
    return words.at(index);
}

void WordleGame::loadWordsFromFile(const QString& fileName, QStringList& words)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString word = in.readLine().trimmed();
            if (!word.isEmpty())
                words << word;
        }
        file.close();
    } else {
        qDebug() << "Failed to open" << fileName;
    }
}

void WordleGame::checkGuess(const QString &guess)
{
    qDebug() << "checkGuess called";
    QString lowercaseGuess = guess.toLower();
    if (!validGuesses.contains(lowercaseGuess)) {
        emit feedback("Invalid guess!");
        return;
    }

    if (guess.length() != targetWord.length()) {
        emit feedback("Invalid guess length!");
        return;
    }

    previousGuesses.append(guess);
    emit previousGuessesChanged();

    if (guess == targetWord.toUpper()) {
        emit feedback("Congratulations! You've guessed the word!\nPress Enter to restart.");
        gameOver = true;
        emit gameOverChanged(true);
        return;
    }

    if (previousGuesses.length() == 6) {
        emit feedback("Sorry, you've run out of guesses! Correct answer was: " + targetWord.toUpper() + "\nPress Enter to restart.");
        gameOver = true;
        emit gameOverChanged(false);
        return;
    }
}


void WordleGame::restart()
{
    qDebug() << "Restart method called!";
    gameOver = false;
    previousGuesses.clear();
    targetWord = selectTargetWord(validWords);
    emit targetWordChanged();
    emit previousGuessesChanged();
    emit gameOverChanged(false);
}

void WordleGame::setCurrentGuess(const QString& guess)
{
    if (m_currentGuess != guess) {
        m_currentGuess = guess;
        emit currentGuessChanged();
    }
}

QString WordleGame::getCurrentGuess() const
{
    return m_currentGuess;
}

QString WordleGame::getTargetWord() const
{
    return targetWord;
}

QStringList WordleGame::getPreviousGuesses() const
{
    return previousGuesses;
}

bool WordleGame::getGameOver() const {
    return gameOver;
}
