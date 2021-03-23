class Time {
  constructor(public timestamp: Date) {}

  label() {
    let message: string;
    let hour = this.timestamp.getHours();

    if (hour < 12 && hour > 6) {
      message = "morning";
    } else if (hour < 18) {
      message = "afternoon"
    } else if (hour < 21){
      message = "evening"
    } else {
      message = "night"
    }

    return message;
  }
}

function greeting() {
  let now = new Time(new Date());
  return `Good ${now.label()}`;
}

document.body.innerHTML = greeting();
