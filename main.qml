import QtQuick 2.14
import QtQuick.Controls 2.14
import WordleGame 1.0

ApplicationWindow {
    visible: true
    width: 370
    height: 400
    title: "lilwordle"

    WordleGame {
        id: game
    }

    Text {
        id: feedbackText
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ListView {
        id: guessesListView
        anchors {
            top: feedbackText.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        spacing: 5
        model: 6
        delegate: Row {
            spacing: 3
            property string guess: {
                if (index === game.previousGuesses.length)
                    return game.currentGuess.toUpperCase()
                else if (index < game.previousGuesses.length)
                    return game.previousGuesses[index].toUpperCase()
                else
                    return ""
            }
            property bool overrideColorBeforeSubmission: {
                if (index === game.previousGuesses.length)
                    return true
                else
                    return false
            }
            Repeater {
                model: game.targetWord.length
                Rectangle {
                    width: 60
                    height: 55
                    radius: 3
                    border.width: 1
                    border.color: "black"
                    color: {
                        var character = guess.charAt(index)
                        var target = game.targetWord.toUpperCase()
                        if (overrideColorBeforeSubmission
                                || (guess.length !== target.length)) {
                            return "gray"
                        } else {
                            if (character === target[index]) {
                                return "green"
                            } else if (target.indexOf(character) !== -1) {
                                return "yellow"
                            }
                        }
                        return "gray"
                    }
                    Text {
                        text: guess.charAt(index)
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }

    Item {
        id: keyHandler
        focus: true

        Keys.onPressed: {
            var key = String.fromCharCode(event.text.charCodeAt(
                                              0)).toUpperCase()
            if (/^[A-Z]$/.test(key) && game.currentGuess.length < 5) {
                game.currentGuess += key
                //console.log("Current guess:", game.currentGuess)
            } else if (event.key === Qt.Key_Backspace
                       && game.currentGuess.length > 0) {
                game.currentGuess = game.currentGuess.substring(
                            0, game.currentGuess.length - 1)
                //console.log("Current guess after backspace:", game.currentGuess)
            } else if (event.key === Qt.Key_Return) {
                if (game.gameOver) {
                    game.restart()
                    feedbackText.text = ""
                } else if (game.currentGuess.length === 5) {
                    game.checkGuess(game.currentGuess)
                }
            }
        }
    }

    Connections {
        target: game
        onFeedback: {
            feedbackText.text = feedback
        }
        onPreviousGuessesChanged: {
            game.currentGuess = ""
            console.log("Current guess cleared")
        }
        onGameOverChanged: {

        }
    }
}
