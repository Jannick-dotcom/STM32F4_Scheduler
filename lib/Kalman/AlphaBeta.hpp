class AlphaBeta{

public:
    struct AlphaBetaParams{
            float alpha; //alpha value (effects x, eg pos)
            float beta; //beta value (effects v, eg vel)
            float xk_1; //current x-estimate 
            float vk_1; //current v-estimate 
    };


private: 
    AlphaBetaParams pab;
    
public:

    AlphaBeta(float x_measured, float alpha, float beta) {
        pab.xk_1 = x_measured; 
        pab.vk_1 = 0; 
        pab.alpha = alpha; 
        pab.beta = beta; 
    }    

    const AlphaBetaParams* step(float x_measured, float dt) {

        float xk_1 = pab.xk_1; 
        float vk_1 = pab.vk_1; 
        float alpha = pab.alpha; 
        float beta = pab.beta; 
        
        float xk; //current system state (ie: position)
        float vk; //derivative of system state (ie: velocity)
        float rk; //residual error 
        
        //update our (estimated) state 'x' from the system (ie pos = pos + vel (last).dt)
        xk = xk_1 + dt * vk_1; 
        //update (estimated) velocity  
        vk = vk_1; 
        //what is our residual error (mesured - estimated) 
        rk = x_measured - xk;  
        //update our estimates given the residual error. 
        xk = xk + alpha * rk; 
        vk = vk + beta/dt * rk; 
        //finished! 
        
        //now all our "currents" become our "olds" for next time 
        pab.vk_1 = vk; 
        pab.xk_1 = xk; 

        return &pab;
    } 
};


