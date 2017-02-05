% helloWorld.m
disp('Hello World!');
disp('I am going to learn MATLAB!');
load startTime;
disp(['I started learning MATLAB on ',startString]);
load secs;
secPerMonth = 30.5*secPerDay;
secPerYear = 12*secPerMonth;
secondConversion = [secPerYear, secPerMonth, secPerDay, secPerHour,...
    secPerMin,1];
currentTime = clock;
elapsedTime = currentTime-start;
t = secondConversion*transpose(elapsedTime);
tau = 1.5*secPerDay;
endOfClass = 5*secPerDay;
currentKnowledge = 1-exp(-t/tau);
disp(['At this time. I know ', num2str(currentKnowledge*100),...
    '% of MATLAB']);
tVec = linspace(0,endOfClass,10000);
knowledgeVec = 1-exp(-tVec/tau);
[val,ind] = min(abs(knowledgeVec-0.5));
halfTime = tVec(ind);
disp(['I will know half of MATLAB after ', num2str(halfTime/secPerDay),...
    ' days!']);
figure;
plot(tVec/secPerDay, knowledgeVec);


