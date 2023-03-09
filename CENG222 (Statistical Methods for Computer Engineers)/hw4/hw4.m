N = 4145; % with alpha = 0.01 and error = 0.02
lambda_poisson = [50,10]; % parameters for poisson and gamma distributions.
alpha_gamma = [190,110];  % the first indexes represent the parameters for car
lambda_gamma=[0.15,0.01]; % and the seconds indexes for truck
TotalWeight=zeros(N,1);
for k=1:N;
    for j=1:2; % do the same simulation for the cars and trucks respectively.
        U = rand; i=0;              % generate random poisson variable Y
        F= exp(-lambda_poisson(j));
	    while (U>=F);
		    i=i+1;
		    F = F+exp(-lambda_poisson(j))*lambda_poisson(j)^i/gamma(i+1);
	    end;
        Y = i;  

        %generate random gamma variables X for all Y's and sum them for
        %total weight of one type of vehicles.
	    weight = 0; 
        for m=1:i;
            X = sum(-1/lambda_gamma(j) * log(rand(alpha_gamma(j),1)));
            weight = weight + X;
        end;
        TotalWeight(k) = TotalWeight(k)+weight; % sum the weights of trucks and cars
    end;
end;

p_est = mean(TotalWeight>200000); %estimated probability
expected_weight = mean(TotalWeight);%expected weight
standard_deviation = std(TotalWeight);%standard deviaton

fprintf('Estimated probability = %f\n',p_est);
fprintf('Expected weight = %f\n',expected_weight);
fprintf('Standard deviation = %f\n',standard_deviation);


