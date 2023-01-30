var { DateTime } = require("luxon");

// make uptimebot server
const express = require("express");
const app = express();

let port = process.env.PORT || 3000;

app.get("/", function (req, res){
    res.send(`{"waktu": "${DateTimeBot()["hour"]}:${DateTimeBot()["minute"]}", "tanggal": "${DateTimeBot()["day"]}-${DateTimeBot()["month"]}-${DateTimeBot()["year"]}"}`);
});

app.listen(port, () => {
    console.log(`Example app is listening on port http://localhost:${port}`);
});


function DateTimeBot() {
    var local = DateTime.local();
    var rezonedString = local.setZone("Asia/Jakarta");

    // get Date
    let year = rezonedString.c.year;
    let month = rezonedString.c.month;
    let day = rezonedString.c.day;

    // get Time
    let hour = rezonedString.c.hour;
    let minute = rezonedString.c.minute;
    let second = rezonedString.c.second;

    return {
        "hour": hour, "minute": minute, "second": second,
        "day": day, "month": month, "year": year
    }
}