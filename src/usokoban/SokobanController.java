/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package usokoban;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Random;
import java.util.ResourceBundle;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.stage.Window;
import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;
import jssc.SerialPortList;


/**
 *
 * @author ssavic
 */
public class SokobanController implements Initializable {
    
    @FXML
    private ComboBox comboBoxPorts;
    @FXML
    private Button startBtn;
    
    private static final int DIM_HEADER = 0xFF;
    private static final int GRID_HEADER = 0xFE;
    private static final int NUM_OF_IMAGES = 7;
    private static final int SCENE_WIDTH = 480;
    private static final int SCENE_HEIGHT = 240;
    private Image [] images = new Image[NUM_OF_IMAGES];
    private Stage stage = null ;
    private ArrayList<ImageView> grid = new ArrayList<>();
    private static boolean ready = false;
    private static boolean initialized = false;
    private int width = 0;
    private int height = 0;
    private GridPane root;
    
    @FXML
    private void handleButtonAction(ActionEvent event) throws IOException{
        if (ready)
        {
            switchScene();
        }
    }
    
    @FXML
    private void handleComboBoxAction(ActionEvent event) throws IOException{
        String serialPortName = (String)
                comboBoxPorts.getSelectionModel().getSelectedItem();
        
        SerialPort serialPort = new SerialPort(serialPortName);
        try {
            serialPort.openPort();

            serialPort.setParams(SerialPort.BAUDRATE_9600,
                        SerialPort.DATABITS_8,
                        SerialPort.STOPBITS_1,
                        SerialPort.PARITY_NONE);

            serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | 
                                  SerialPort.FLOWCONTROL_RTSCTS_OUT);

            serialPort.addEventListener(new SerialPortEventListener() {
                
                private void waitForData(int data) throws SerialPortException{
                    byte buffer = 0;
                    while(buffer != (byte)data)
                    {
                        buffer = serialPort.readBytes(1)[0];
                        System.out.println(buffer);
                    }
                }
                
                @Override
                public void serialEvent(SerialPortEvent spe) {
                    if(spe.isRXCHAR() && spe.getEventValue() > 0) {
                        try {
                            if (!initialized){
                                
                                waitForData(DIM_HEADER);                            
                                width = serialPort.readBytes(1)[0];
                                height = serialPort.readBytes(1)[0];
                                System.out.println(width);
                                System.out.println(height);
                                
                                for(int y = 0; y < height; y++){
                                    for(int x = 0; x < width; x++){
                                        ImageView iView = new ImageView();
                                        iView.setImage(images[0]);
                                        iView.setFitHeight(SCENE_HEIGHT / height);
                                        iView.setFitWidth(SCENE_WIDTH / width);
                                        iView.setPreserveRatio(true);
                                        grid.add(iView);

                                        root.setRowIndex(iView,y);
                                        root.setColumnIndex(iView,x);    
                                        root.getChildren().add(iView);
                                    }
                                }
                                ready = true;
                            }
                            
                            int imageToPick = 0;
                                
                            waitForData(GRID_HEADER);
                            for(int i = 0; i < height; i++)
                                for(int j = 0; j < width; j++){
                                    imageToPick = serialPort.readBytes(1)[0];
                                    grid.get(i*width + j).setImage(images[imageToPick]);
                                }
                        }
                        catch (SerialPortException ex) {
                            System.out.println("Error in receiving string from serial port: " + ex);
                        }
                    }
                }
            }, SerialPort.MASK_RXCHAR);
            
        }
        catch (SerialPortException ex) {
            System.out.println("Some error ocurred: " + ex);
        }   
    }
    
    private void switchScene(){
        Scene oldScene = startBtn.getScene();
        Window window = oldScene.getWindow();
        stage = (Stage) window;   
        Scene scene = new Scene(root, SCENE_WIDTH, SCENE_HEIGHT);    
        stage.setScene(scene);
        stage.show();
        initialized = true;
    }
    
    private void initPortList(){
        ObservableList<String> portList = FXCollections.observableArrayList();

        String[] serialPortNames = SerialPortList.getPortNames();
        
        for(String name: serialPortNames){
            System.out.println(name);
            portList.add(name);
        }
        
        comboBoxPorts.getItems().addAll(portList);
    }
    
    private void prepareResources(){
        root = new GridPane();
        
        String resourcesPath = System.getProperty("user.dir") + 
                File.separator + "resources" 
                + File.separator + "grpx" + File.separator;
        
        for (int i = 0; i < NUM_OF_IMAGES; i++){
            String filename = String.valueOf(i) + ".png";
            images[i] = new Image("file:" + resourcesPath + filename);
        }
        
        System.out.println(images[0].getHeight());
    }
            
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        initPortList(); 
        prepareResources();
    }    
    
}
