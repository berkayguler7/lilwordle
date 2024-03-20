#ifndef WORDLEGAME_H
#define WORDLEGAME_H

#include <QObject>
#include <QStringList>

class WordleGame : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList previousGuesses READ getPreviousGuesses NOTIFY previousGuessesChanged)
    Q_PROPERTY(QString targetWord READ getTargetWord NOTIFY targetWordChanged)
    Q_PROPERTY(bool gameOver READ getGameOver NOTIFY gameOverChanged)
    Q_PROPERTY(QString currentGuess READ getCurrentGuess WRITE setCurrentGuess NOTIFY currentGuessChanged)

public:
    explicit WordleGame(QObject *parent = nullptr);
    Q_INVOKABLE void restart();
    QStringList getPreviousGuesses() const;
    QString getTargetWord() const;
    bool getGameOver() const;
    QString getCurrentGuess() const;
    void setCurrentGuess(const QString& guess);

signals:
    void feedback(const QString& feedback);
    void previousGuessesChanged();
    void targetWordChanged();
    void gameOverChanged(bool victory);
    void currentGuessChanged();

public slots:
    void checkGuess(const QString& guess);

private:
    QString targetWord;
    QStringList validWords;
    QStringList validGuesses;
    QStringList previousGuesses;
    bool gameOver;
    QString m_currentGuess;

    QString selectTargetWord(const QStringList& words);
    void loadWordsFromFile(const QString& fileName, QStringList& words);
};

#endif // WORDLEGAME_H
