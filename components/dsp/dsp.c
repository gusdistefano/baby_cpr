#include "dsp.h"

esp_err_t kalman_init(kalmanFilter_t *kf, float q, float r, float initial_value)
{
    kf->q = q;             //!< Set process variance; higher values make the filter more responsive to changes.
    kf->r = r;             //!< Set measurement variance; higher values decrease reliance on sensor data.
    kf->x = initial_value; //!< Set the initial estimated state.
    kf->p = 1.0;           //!< Initial estimation error; can be adjusted based on expected initial uncertainty.
    kf->k = 0.0;           //!< Initial Kalman gain, starts at 0 and will update dynamically.
    return ESP_OK;
}

float kalman_update(kalmanFilter_t *kf, const float *measurement)
{
    // Prediction: Update estimation error (p) by adding process variance (q).
    kf->p = kf->p + kf->q; //!< Predict new error by accounting for process variance.

    // Update Kalman gain.
    kf->k = kf->p / (kf->p + kf->r); //!< Calculate Kalman gain; higher values indicate more trust in the measurement.

    // Update estimated state using the new measurement.
    kf->x = kf->x + kf->k * ((*measurement) - kf->x); //!< Adjust the estimated state based on the new measurement.

    // Update the estimated error.
    kf->p = (1 - kf->k) * kf->p; //!< Update estimation error as the filter becomes more confident.

    // Return the updated estimated state.
    return kf->x;
}

void low_pass_filter(float *filtered_value, const float *current_value, const float alpha)
{
    *filtered_value = (alpha) * (*filtered_value) + (1 - (alpha)) * (*current_value); //!< Apply low-pass filtering.
}


