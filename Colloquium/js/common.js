/*
 *  SETUP
 */
let stat = new Map([
    ['totalQuestions', 0],
    ['totalFailQuestions', 0],
    ['totalSuccessQuestions', 0],
    ['questionsArray', Array()]
]);
let questionsArray = [];
let subject = "";
let questionID = 0;
let answer = "";
let timer = 0;
let emergency_timer = 0;
let request = new XMLHttpRequest();
let requestURL = "/";

let planningTimer = setInterval(updateTimer, 1000);
clearInterval(planningTimer);

const requestURLs = ['./json/discrete.json', './json/linalg.json', './json/mathanalysis.json'];

function getRandomQuestion() {
    return Math.floor(Math.random() * questionsArray.length);
}

function showTimer() {
    let sec = Math.floor(timer / 1000);
    let min = Math.floor(sec / 60);

    sec -= min * 60;

    document.querySelector("#question-timer-min").innerHTML = min;
    document.querySelector("#question-timer-sec").innerHTML = sec;
    if (sec < 10)
        document.querySelector("#question-timer-sec").innerHTML = '0' + sec;
}

function renderQuestion() {
    questionID = getRandomQuestion();
    document.querySelector("#question-subject").innerHTML = subject;
    document.querySelector("#question-number").innerHTML = questionsArray[questionID]["ID"];
    document.querySelector("#question-text").innerHTML = questionsArray[questionID]["text"];
    showTimer();
}

function load() {
    stopTimer();

    let needleSubject = document.querySelector("#category").innerHTML;
    switch (needleSubject) {
        default: {
            document.querySelector(".nav_active").classList.remove("nav_active");
            document.querySelector("#nav_home").classList.add("nav_active");
            requestURL = requestURLs[Math.floor(Math.random() * 2)];
            break;
        }
        case 'Maths': {
            document.querySelector(".nav_active").classList.remove("nav_active");
            document.querySelector("#nav_math").classList.add("nav_active");
            requestURL = requestURLs[2];
            break;
        }
        case 'Linalg': {
            document.querySelector(".nav_active").classList.remove("nav_active");
            document.querySelector("#nav_linalg").classList.add("nav_active");
            requestURL = requestURLs[1];
            break;
        }
        case 'DiscMaths': {
            document.querySelector(".nav_active").classList.remove("nav_active");
            document.querySelector("#nav_dm").classList.add("nav_active");
            requestURL = requestURLs[0];
            break;
        }
    }

    request.open('GET', requestURL);
    request.responseType = 'json';
    request.send();

    request.onload = function () {
        let object = request.response;

        stat.set("totalQuestions", stat.get("totalQuestions") + 1);

        let tmp = new Map([
            ["subject", object["subject"]],
            ["id", questionID],
            ["elapsedTime", 0],
            ["status", "active"]
        ]);

        let t = stat.get("questionsArray");
        t.push(tmp);
        stat.set("questionsArray", t);

        questionsArray = object["questions"];
        subject = object["subject"];
        timer = object["timer"];
        emergency_timer = timer;
        renderQuestion();
        answer = object["questions"][questionID]["answer"];
        emergency_timer = timer;
        startTimer();
        console.log(stat);
    }
}

function updateTimer() {
    let currentQuestion = stat.get("totalQuestions") - 1;
    timer -= 1000;

    let t = stat.get("questionsArray");
    t[currentQuestion].set("elapsedTime", emergency_timer - timer);

    if (timer < 10000) {
        document.querySelector(".playground_body_timer").style.color = "#ffcc00";
        document.querySelector(".playground_body_timer").style.textDecorationColor = "#ffcc00";
    }
    if (timer < 5000) {
        document.querySelector(".playground_body_timer").style.color = "#d53e07";
        document.querySelector(".playground_body_timer").style.textDecorationColor = "#d53e07";
    }
    if (!(timer < 10000) || (timer < 0)) {
        document.querySelector(".playground_body_timer").style.color = "#4f4f4f";
        document.querySelector(".playground_body_timer").style.textDecorationColor = "#4f4f4f";
    }

    if (timer <= 0) {
        t[currentQuestion].set("status", "failed");
        stat.set("totalFailQuestions", stat.get("totalFailQuestions") + 1);
        stat.set("questionsArray", t);
        stopTimer();
    }
    showTimer()
}

function clearTimer() {
    stopTimer();
    timer = emergency_timer;
    showTimer();
}

function startTimer() {
    if (timer > 0)
        planningTimer = setInterval(updateTimer, 1000);
}

function stopTimer() {
    clearInterval(planningTimer);
}

function removeStat() {
    stat = new Map([
        ['totalQuestions', 0],
        ['totalFailQuestions', 0],
        ['totalSuccessQuestions', -1],
        ['questionsArray', Array()]
    ]);
}

function makeAnswer() {
    document.querySelector(".answer_body").innerHTML = answer;
}

function makeStat() {
    document.querySelector("#total_questions").innerHTML = stat.get("totalQuestions");
    document.querySelector("#solved_questions").innerHTML = stat.get("totalSuccessQuestions");
    document.querySelector("#failed_questions").innerHTML = stat.get("totalFailQuestions");

    let avg_time = 0;
    let t = stat.get("questionsArray");
    for (let i = 0; i < t.length; ++i) {
        avg_time += t[i].get("elapsedTime");
    }
    avg_time /= stat.get("totalQuestions") - 1;

    document.querySelector("#average_time").innerHTML = Math.floor((avg_time / 1000)) + ' секунд(ы)';

    document.querySelector(".stat_table").innerHTML = "<div class=\"stat_table_item\">\n" +
        "            <div class=\"stat_subject\">Предмет</div>\n" +
        "            <div class=\"stat_id\">Вопрос #</div>\n" +
        "            <div class=\"stat_status\">Резульат</div>\n" +
        "            <div class=\"stat_time\">Время</div>\n" +
        "        </div>"

    for (let i = 0; i < t.length; ++i) {
        document.querySelector(".stat_table").innerHTML += "<div class=\"stat_table_item\">\n" +
            "            <div class='" + t[i].get("status") + " stat_subject'>" + t[i].get("subject") + "</div>\n" +
            "            <div class='" + t[i].get("status") + " stat_id'>" + (t[i].get("id") + 1) + "</div>\n" +
            "            <div class='" + t[i].get("status") + " stat_status'>" + t[i].get("status") + "</div>\n" +
            "            <div class='" + t[i].get("status") + " stat_time'>" + (t[i].get("elapsedTime") / 1000) + "</div>\n" +
            "        </div>";
    }
}

function addStatEntry(status) {
    let currentQuestion = stat.get("totalQuestions") - 1;
    let t = stat.get("questionsArray");
    if (t[currentQuestion].get("status") !== "active")
        return;
    t[currentQuestion].set("elapsedTime", emergency_timer - timer);
    switch (status) {
        case 'success': {
            t[currentQuestion].set("status", "done");
            stat.set("totalSuccessQuestions", stat.get("totalSuccessQuestions") + 1);
            break;
        }
        case 'fail': {
            t[currentQuestion].set("status", "failed");
            stat.set("totalFailQuestions", stat.get("totalFailQuestions") + 1);
            break;
        }
        case 'skip': {
            t[currentQuestion].set("status", "not_solved");
            stat.set("totalFailQuestions", stat.get("totalFailQuestions") + 1);
        }
    }
    stat.set("questionsArray", t);
}

function incorrectAnswer() {
    closeAnswer();
    addStatEntry('fail');
}

function correctAnswer() {
    closeAnswer();
    addStatEntry('success')
}

function notSolved() {
    addStatEntry('skip');
}

function openStat() {
    stopTimer();
    makeStat();
    document.querySelector('.stat').style.opacity = '1';
    document.querySelector('.stat').style.zIndex = '100';
}

function closeStat() {
    document.querySelector('.stat').style.opacity = '0';
    document.querySelector('.stat').style.zIndex = '-1';
    startTimer();
}

function openAnswer() {
    stopTimer();
    makeAnswer();
    document.querySelector('.answer').style.opacity = '1';
    document.querySelector('.answer').style.zIndex = '100';
}

function closeAnswer() {
    document.querySelector('.answer').style.opacity = '0';
    document.querySelector('.answer').style.zIndex = '-1';
}

function skipQuestion() {
    load();
    notSolved();
}

function switchSubject(subject) {
    removeStat();

    switch (subject) {
        case 'mathanalysis': {
            document.querySelector('#category').innerHTML = 'Maths';
            break;
        }
        case 'discrete': {
            document.querySelector('#category').innerHTML = 'DiscMaths';
            break;
        }
        case 'linalg': {
            document.querySelector('#category').innerHTML = 'Linalg';
            break;
        }
        case 'any': {
            document.querySelector('#category').innerHTML = 'Any';
            break;
        }
    }

    load();
}
