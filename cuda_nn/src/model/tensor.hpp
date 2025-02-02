#ifndef CUDA_NN_TENSOR_HPP
#define CUDA_NN_TENSOR_HPP


#include <vector>
#include <random>

class SparseLinearLayer;  // Forward declaration

class Tensor {
protected:
    std::vector<unsigned int> _shape;  // Shape of the matrix
    unsigned int _total;  // Flattened shape (stored for performance reasons)
    float* _data_host;  // Actual data of the Tensor on host (stored as a 1D array for performance reasons)
    float* _data_device;  // Actual data of the Tensor on device (stored as a 1D array for performance reasons)
    bool _on_device;  // Flag to track data location

    friend class SparseLinearLayer;  // Declare as "friend" to let it access private _data field
public:
    // Standard constructor
    explicit Tensor(const std::vector<unsigned int> &shape);
    // Copy constructor
    Tensor(const Tensor &tensor);
    // Move constructor
    Tensor(Tensor &&tensor) noexcept;
    // Destructor
    ~Tensor();

    // Host&device management
    void allocate_device();
    void free_device();
    void host2device(bool async = false);
    void device2host();

    // Init method
    void init(std::uniform_real_distribution<float> d, std::mt19937 &gen);

    // Getter
    std::vector<unsigned int> get_shape() const { return _shape; }
    unsigned int get_total() const { return _total; }

    // Custom subscript operator (for host memory)
    float& operator[](int i) const { return _data_host[i]; }
    // Equality copy operator
    Tensor& operator=(const Tensor &tensor);
    // Equality move operator
    Tensor& operator=(Tensor &&tensor) noexcept;

    // Custom string representation for print
    virtual void print(std::ostream& where) const = 0;
    friend std::ostream& operator<<(std::ostream&, const Tensor&);
};


#endif //CUDA_NN_TENSOR_HPP