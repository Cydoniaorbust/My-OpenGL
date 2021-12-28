using System;
using System.IO;
using System.Drawing;
using System.Drawing.Imaging;
using System.Globalization;
using System.Windows.Forms;
using System.Collections.Generic;
using OpenTK.Graphics.OpenGL4;
using GlmSharp;
using Assimp;

namespace WindowsFormsApp1 {
    public enum Cam_Mov { FORWARD, BACKWARD, LEFT, RIGHT };
    public struct Vertex {
        public vec3 Position;
        public vec3 Normal;
        public vec2 TexCoords;
        public vec3 Tangent;
        public vec3 Bitangent;
    };
    public struct Texture {
        public int id;
        public string type;
        public string path;
    };
    
    public partial class Main_form : Form {
        uint nbFrames = 0;
        bool loaded = false;
        float lastX, lastY, DTime = 0;
        vec3 LightDir = new vec3(-0.2f, -1.0f, -0.3f);

        vec3 LightAmb = new vec3(0.5f);
        vec3 LightDifSpot = new vec3(0.0f);
        vec3 LightDifDir = new vec3(0.5f);
        
        Model ObjModel;
        DateTime Last, Delta;
        Camera Cam1 = new Camera(new vec3(0.0f, 3.0f, -2.5f), new vec3(0.0f, 1.0f, 0.0f), 90.0f, -30.0f);
        Shader ObjShader, SimpShader;
        mat4 pos = mat4.Scale(1);

        public Main_form() { InitializeComponent(); }
        void GLCtrl_Load(object sender, EventArgs e) {
            GLCtrl.MakeCurrent();
            GL.Viewport(0, 0, GLCtrl.Width, GLCtrl.Height);

            GL.Enable(EnableCap.DepthTest);
            GL.Enable(EnableCap.CullFace);
            GL.CullFace(CullFaceMode.Back);
            GL.FrontFace(FrontFaceDirection.Ccw);

            ObjShader = new Shader("Resources/Shader/Shader.vert", "Resources/Shader/Shader.frag");
            SimpShader = new Shader("Resources/Shader/Simp.vert", "Resources/Shader/Simp.frag");
            ObjModel = new Model("Resources/Model/nano/nanosuit.obj");

            Application.Idle += new EventHandler(Application_Idle);
            Delta = DateTime.Now;
            loaded = true;
        }
        void Application_Idle(object sender, EventArgs e) { GLCtrl.Invalidate(); }
        void GLCtrl_Paint(object sender, PaintEventArgs e) {
            //Start
            if (!loaded) return;
            //Preparations
            DTime = (float)((DateTime.Now - Last).TotalSeconds);
            Last = DateTime.Now;
            mat4 view = Cam1.GetViewMatrix();
            mat4 projection = mat4.Perspective((float)(Math.PI * Cam1.Zoom / 180.0), GLCtrl.Width / GLCtrl.Height, 0.1f, 1000.0f);
            GL.ClearColor(GLCtrl.BackColor);
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            //Drawing
            DrawAxes(SimpShader, view, projection);
            DrawScene(ObjShader, view, projection, ObjModel);
            //FPS counter
            nbFrames++;
            if (DateTime.Now.Second - Delta.Second >= 1) {
                toolStripStatusLabel_x.Text = (Cam1.Position.x).ToString();
                toolStripStatusLabel_y.Text = (Cam1.Position.y).ToString();
                toolStripStatusLabel_z.Text = (Cam1.Position.z).ToString();
                toolStripStatusLabel_FPS.Text = nbFrames + " fps\n";
                nbFrames = 0;
                Delta += DateTime.Now - Delta;
            }
            //Finish
            //System.Threading.Thread.Sleep(10);
            GLCtrl.SwapBuffers();
        }
        void Form1_FormClosing(object sender, FormClosingEventArgs e) { Application.Idle -= Application_Idle; }

        void GLCtrl_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e) {
            if (e.Button == MouseButtons.Left) {
                Cursor.Hide();
                lastX = e.X;
                lastY = e.Y;
            }
        }
        void GLCtrl_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e) {
            if (e.Button == MouseButtons.Left) {
                float t = Cam1.Yaw;
                Cam1.ProcessMouseMovement(e.X - lastX, lastY - e.Y);
                t -= Cam1.Yaw;
                pos *= mat4.Rotate((float)(Math.PI * t / 180.0), new vec3(0, 1, 0));
                lastX = e.X;
                lastY = e.Y;
            }
        }
        //if (e.Button == MouseButtons.Middle) { Cam1.ProcessMouseScroll(e.Delta); }
        void GLCtrl_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e) { if (e.Button == MouseButtons.Left) Cursor.Show(); }
        void GLCtrl_KeyDown(object sender, KeyEventArgs e) {
            vec3 t = Cam1.Position;
            if (e.KeyCode == Keys.Escape) Environment.Exit(0);
            if (e.KeyCode == Keys.W) Cam1.ProcessKeyboard(Cam_Mov.FORWARD, DTime);
            if (e.KeyCode == Keys.S) Cam1.ProcessKeyboard(Cam_Mov.BACKWARD, DTime);
            if (e.KeyCode == Keys.A) Cam1.ProcessKeyboard(Cam_Mov.LEFT, DTime);
            if (e.KeyCode == Keys.D) Cam1.ProcessKeyboard(Cam_Mov.RIGHT, DTime);
            t = Cam1.Position - t;
            pos *= mat4.Translate(t);
        }

        void DrawAxes(Shader Shader, mat4 view, mat4 projection) {
            float[] Axis = {
                1000.0f, 0.0f, 0.0f,-1000.0f, 0.0f, 0.0f,
                0.0f, 1000.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1000.0f, 0.0f, 0.0f,-1000.0f
                };
            //Assigning
            GL.GenVertexArrays(1, out int VAO_a);
            GL.GenBuffers(1, out int VBO_a);
            GL.BindVertexArray(VAO_a);
            GL.BindBuffer(BufferTarget.ArrayBuffer, VBO_a);
            GL.BufferData(BufferTarget.ArrayBuffer, 72, Axis, BufferUsageHint.StaticDraw);
            GL.VertexAttribPointer(0, 3, VertexAttribPointerType.Float, false, 0, 0);
            GL.EnableVertexAttribArray(0);
            //Shader
            Shader.Use();
            Shader.SetMat4("view", view);
            Shader.SetMat4("projection", projection);
            Shader.SetMat4("model", mat4.Translate(0, 0, 0));
            //Drawing
            GL.LineWidth(2.0f);
            GL.BindVertexArray(VAO_a);
            Shader.SetVec3("color", 1.0f, 0.0f, 1.0f); GL.DrawArrays(OpenTK.Graphics.OpenGL4.PrimitiveType.Lines, 0, 2);
            Shader.SetVec3("color", 0.0f, 1.0f, 0.0f); GL.DrawArrays(OpenTK.Graphics.OpenGL4.PrimitiveType.Lines, 2, 2);
            Shader.SetVec3("color", 1.0f, 0.0f, 1.0f); GL.DrawArrays(OpenTK.Graphics.OpenGL4.PrimitiveType.Lines, 4, 2);
            GL.BindVertexArray(0);
            //Cleaning
            GL.DeleteVertexArrays(1, ref VAO_a);
            GL.DeleteBuffers(1, ref VBO_a);
        }
        void DrawScene(Shader Shader, mat4 view, mat4 projection, Model model) {
            Shader.Use();
            Shader.SetMat4("view", view);
            Shader.SetMat4("projection", projection);
            Shader.SetMat4("model", pos * mat4.Scale(0.1f)); // mat4.Rotate((float)(Math.PI / 180 * 90), new vec3(-1, 0, 0)) * mat4.Scale(0.01f));
            //Basic
            Shader.SetVec3("ViewPos", Cam1.Position);
            Shader.SetVec3("Ambient", LightAmb);
            //Directional
            Shader.SetVec3("DirLight.direction", LightDir);
            Shader.SetVec3("DirLight.diffuse", LightDifDir);
            //SpotLight
            Shader.SetVec3("SpotLight.position", Cam1.Position);
            Shader.SetVec3("SpotLight.direction", Cam1.Front);
            Shader.SetVec3("SpotLight.diffuse", LightDifSpot);
            ObjModel.Draw(Shader);
        }

        private void trackBar_Ambient_Scroll(object sender, EventArgs e) {
            float t = trackBar_Ambient.Value * 0.01f;
            LightAmb = new vec3(t);
            int t1 = (int)((LightAmb.x + LightDifDir.x) * 127.5);
            GLCtrl.BackColor = Color.FromArgb(t1, t1, t1);
            textBox_Ambient.Text = String.Format("{0:0.##}", t.ToString());
        }
        private void trackBar_Diffuse_Directional_Scroll(object sender, EventArgs e) {
            float t = trackBar_Diffuse_Directional.Value * 0.01f;
            LightDifDir = new vec3(t);
            int t1 = (int)((LightAmb.x + LightDifDir.x) * 127.5);
            GLCtrl.BackColor = Color.FromArgb(t1, t1, t1);
            textBox_Diffuse_Directional.Text = String.Format("{0:0.##}", t.ToString());
        }
        private void trackBar_Diffuse_Lamp_Scroll(object sender, EventArgs e) {
            float t = trackBar_Diffuse_Lamp.Value * 0.01f;
            LightDifSpot = new vec3(t);
            textBox_Diffuse_Lamp.Text = String.Format("{0:0.##}", t.ToString());
        }
        private void cB_Polygon_Mode_CheckedChanged(object sender, EventArgs e) {
            if (checkButton_Polygon_Mode.Checked) GL.PolygonMode(MaterialFace.FrontAndBack, PolygonMode.Fill);
            else GL.PolygonMode(MaterialFace.FrontAndBack, PolygonMode.Line);
        }
    }
    public class Camera {
        public vec3 Position;
        public vec3 Front;
        public vec3 Up;
        public vec3 Right;
        public vec3 WorldUp;
        public float Yaw;
        public float Pitch;
        public float MovementSpeed;
        public float MouseSensitivity;
        public float Zoom;

        public Camera() {
            Position = new vec3(0.0f);
            WorldUp = new vec3(0.0f, 1.0f, 0.0f);
            Yaw = 0.0f;
            Pitch = 0.0f;
            Front = new vec3(0.0f, 0.0f, -1.0f);
            MovementSpeed = 20.0f;
            MouseSensitivity = 0.1f;
            Zoom = 45.0f;
            UpdateCameraVectors();
        }
        public Camera(vec3 position, vec3 up, float yaw, float pitch) : this() {
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;
            UpdateCameraVectors();
        }
        public Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : this() {
            Position = new vec3(posX, posY, posZ);
            WorldUp = new vec3(upX, upY, upZ);
            Yaw = yaw;
            Pitch = pitch;
            UpdateCameraVectors();
        }

        public mat4 GetViewMatrix() { return mat4.LookAt(Position, Position + Front, Up); }
        public void ProcessKeyboard(Cam_Mov direction, float deltaTime) {
            float velocity = MovementSpeed * deltaTime;
            if (direction == Cam_Mov.FORWARD) Position += Front * velocity;
            if (direction == Cam_Mov.BACKWARD) Position -= Front * velocity;
            if (direction == Cam_Mov.LEFT) Position -= Right * velocity;
            if (direction == Cam_Mov.RIGHT) Position += Right * velocity;
            Position.y = 3.0f;
        }
        public void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
            xoffset *= MouseSensitivity;
            yoffset *= MouseSensitivity;
            Yaw += xoffset;
            Pitch += yoffset;
            // Make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrainPitch) {
                if (Pitch > 89.0f) Pitch = 89.0f;
                if (Pitch < -89.0f) Pitch = -89.0f;
            }
            // Update Front, Right and Up Vectors using the updated Eular angles
            UpdateCameraVectors();
        }
        public void ProcessMouseScroll(float yoffset) {
            if (Zoom >= 1.0f && Zoom <= 45.0f) Zoom -= yoffset;
            if (Zoom <= 1.0f) Zoom = 1.0f;
            if (Zoom >= 45.0f) Zoom = 45.0f;
        }
        public void UpdateCameraVectors() {
            // Calculate the new Front vector
            vec3 front;
            front.x = (float)(Math.Cos(Math.PI * Yaw / 180.0) * Math.Cos(Math.PI * Pitch / 180.0));
            front.y = (float)(Math.Sin(Math.PI * Pitch / 180.0));
            front.z = (float)(Math.Sin(Math.PI * Yaw / 180.0) * Math.Cos(Math.PI * Pitch / 180.0));
            Front = front.Normalized;
            // Also re-calculate the Right and Up vector
            Right = (vec3.Cross(Front, WorldUp)).Normalized;
            // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            Up = (vec3.Cross(Right, Front)).Normalized;
        }
    };
    public class Shader {
        int ID;
        public void Use() { GL.UseProgram(ID); }
        public Shader(string vertexPath, string fragmentPath) {
            StreamReader vShaderFile, fShaderFile;
            string vCode = "", fCode = "";
            int vertex = GL.CreateShader(ShaderType.VertexShader);
            int fragment = GL.CreateShader(ShaderType.FragmentShader);
            vertexPath = Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, vertexPath));
            fragmentPath = Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, fragmentPath));

            try {
                vShaderFile = new StreamReader(vertexPath, System.Text.Encoding.GetEncoding(1251));
                fShaderFile = new StreamReader(fragmentPath, System.Text.Encoding.GetEncoding(1251));
                vCode = vShaderFile.ReadToEnd();
                fCode = fShaderFile.ReadToEnd();
            }
            catch { MessageBox.Show("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ"); }

            GL.ShaderSource(vertex, vCode);
            GL.CompileShader(vertex);
            CheckCompileErrors(vertex, "VERTEX");

            GL.ShaderSource(fragment, fCode);
            GL.CompileShader(fragment);
            CheckCompileErrors(fragment, "FRAGMENT");

            ID = GL.CreateProgram();
            GL.AttachShader(ID, vertex);
            GL.AttachShader(ID, fragment);
            GL.LinkProgram(ID);
            CheckCompileErrors(ID, "PROGRAM");

            GL.DeleteShader(vertex);
            GL.DeleteShader(fragment);
        }
        public Shader(string vertexPath, string fragmentPath, string geometryPath) {
            StreamReader vShaderFile, fShaderFile, gShaderFile;
            string vCode = "", fCode = "", gCode = "";
            int vertex = GL.CreateShader(ShaderType.VertexShader);
            int fragment = GL.CreateShader(ShaderType.FragmentShader);
            int geometry = GL.CreateShader(ShaderType.GeometryShader);
            vertexPath = Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, vertexPath));
            fragmentPath = Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, fragmentPath));
            geometryPath = Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, geometryPath));

            try {
                vShaderFile = new StreamReader(vertexPath, System.Text.Encoding.GetEncoding(1251));
                fShaderFile = new StreamReader(fragmentPath, System.Text.Encoding.GetEncoding(1251));
                gShaderFile = new StreamReader(geometryPath, System.Text.Encoding.GetEncoding(1251));
                vCode = vShaderFile.ReadToEnd();
                fCode = fShaderFile.ReadToEnd();
                gCode = gShaderFile.ReadToEnd();
            }
            catch { MessageBox.Show("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ"); }

            GL.ShaderSource(vertex, vCode);
            GL.CompileShader(vertex);
            CheckCompileErrors(vertex, "VERTEX");

            GL.ShaderSource(fragment, fCode);
            GL.CompileShader(fragment);
            CheckCompileErrors(fragment, "FRAGMENT");

            GL.ShaderSource(geometry, gCode);
            GL.CompileShader(geometry);
            CheckCompileErrors(geometry, "GEOMETRY");

            ID = GL.CreateProgram();
            GL.AttachShader(ID, vertex);
            GL.AttachShader(ID, fragment);
            GL.AttachShader(ID, geometry);
            GL.LinkProgram(ID);
            CheckCompileErrors(ID, "PROGRAM");

            GL.DeleteShader(vertex);
            GL.DeleteShader(fragment);
            GL.DeleteShader(geometry);
        }
        void CheckCompileErrors(int shader, string type) {
            if (type != "PROGRAM") {
                GL.GetShader(shader, ShaderParameter.CompileStatus, out int success);
                if (success == 0) { MessageBox.Show("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " + GL.GetShaderInfoLog(shader)); }
            }
            else {
                GL.GetProgram(shader, GetProgramParameterName.LinkStatus, out int success);
                if (success == 0) { MessageBox.Show("ERROR::PROGRAM_LINKING_ERROR of type: " + GL.GetProgramInfoLog(shader)); }
            }
        }
        public void SetInt(string name, int value) { GL.Uniform1(GL.GetUniformLocation(ID, name), value); }
        public void SetFloat(string name, float value) { GL.Uniform1(GL.GetUniformLocation(ID, name), value); }
        public void SetVec3(string name, vec3 value) { GL.Uniform3(GL.GetUniformLocation(ID, name), value.x, value.y, value.z); }
        public void SetVec3(string name, float x, float y, float z) { GL.Uniform3(GL.GetUniformLocation(ID, name), x, y, z); }
        public void SetMat4(string name, mat4 mat) { GL.UniformMatrix4(GL.GetUniformLocation(ID, name), 1, false, mat.Values1D); }
    };
    public class Model {
        public List<Texture> textures_loaded = new List<Texture>(100);
        public List<MyMesh> meshes = new List<MyMesh>(100);
        public Model(string path) { LoadModel(path); }
        public void Draw(Shader shader) { for (int i = 0; i < meshes.Count; i++) meshes[i].Draw(shader); }
        void LoadModel(string path) {
            Scene scene = new AssimpContext().ImportFile(path, PostProcessSteps.CalculateTangentSpace | PostProcessSteps.FlipUVs);
            if (scene.SceneFlags == 0 & SceneFlags.Incomplete == 0) return;
            ProcessNode(scene.RootNode, scene);
        }
        void ProcessNode(Node node, Scene scene) {
            for (int i = 0; i < node.MeshCount; i++) {
                Mesh mesh = scene.Meshes[node.MeshIndices[i]];
                meshes.Add(ProcessMesh(mesh, scene));
            }
            for (int i = 0; i < node.ChildCount; i++) ProcessNode(node.Children[i], scene);
        }
        MyMesh ProcessMesh(Mesh mesh, Scene scene) {
            List<Vertex> vertices = new List<Vertex>(mesh.VertexCount);
            List<int> indices = new List<int>(mesh.GetIndices());
            List<Texture> textures = new List<Texture>(mesh.TextureCoordinateChannelCount);
            for (int i = 0; i < mesh.VertexCount; i++) {
                Vertex vertex = new Vertex();
                vec3 vector;
                vector.x = mesh.Vertices[i].X;
                vector.y = mesh.Vertices[i].Y;
                vector.z = mesh.Vertices[i].Z;
                vertex.Position = vector;
                vector.x = mesh.Normals[i].X;
                vector.y = mesh.Normals[i].Y;
                vector.z = mesh.Normals[i].Z;
                vertex.Normal = vector;
                if (mesh.TextureCoordinateChannelCount != 0) {
                    vec2 vec;
                    vec.x = mesh.TextureCoordinateChannels[0][i].X;
                    vec.y = mesh.TextureCoordinateChannels[0][i].Y;
                    vertex.TexCoords = vec;
                }
                else vertex.TexCoords = new vec2(0);
                vector.x = mesh.Tangents[i].X;
                vector.y = mesh.Tangents[i].Y;
                vector.z = mesh.Tangents[i].Z;
                vertex.Tangent = vector;
                vector.x = mesh.BiTangents[i].X;
                vector.y = mesh.BiTangents[i].Y;
                vector.z = mesh.BiTangents[i].Z;
                vertex.Bitangent = vector;
                vertices.Add(vertex);
            }
            for (int i = 0; i < mesh.FaceCount; i++) {
                Face face = mesh.Faces[i];
                for (int j = 0; j < face.IndexCount; j++) indices.Add(face.Indices[j]);
            }
            Material material = scene.Materials[mesh.MaterialIndex];
            List<Texture> diffuseMaps = LoadMaterialTextures(material, TextureType.Diffuse, "texture_diffuse"); textures.AddRange(diffuseMaps);
            List<Texture> specularMaps = LoadMaterialTextures(material, TextureType.Specular, "texture_specular"); textures.AddRange(specularMaps);
            List<Texture> normalMaps = LoadMaterialTextures(material, TextureType.Normals, "texture_normal"); textures.AddRange(normalMaps);
            List<Texture> heightMaps = LoadMaterialTextures(material, TextureType.Height, "texture_height"); textures.AddRange(heightMaps);
            return new MyMesh(vertices, indices, textures);
        }
        List<Texture> LoadMaterialTextures(Material mat, TextureType type, string typeName) {
            List<Texture> textures = new List<Texture>(mat.GetMaterialTextureCount(type));
            for (int i = 0; i < mat.GetMaterialTextureCount(type); i++) {
                mat.GetMaterialTexture(type, i, out TextureSlot str);
                bool skip = false;
                for (int j = 0; j < textures_loaded.Count; j++)
                    if (textures_loaded[j].path == str.FilePath) {
                        textures.Add(textures_loaded[j]);
                        skip = true;
                        break;
                    }
                if (!skip) {
                    Texture texture;
                    texture.id = LoadTextureFromFile("Resources/Model/nano/" + str.FilePath);
                    texture.type = typeName;
                    texture.path = str.FilePath;
                    textures.Add(texture);
                    textures_loaded.Add(texture);
                }
            }
            return textures;
        }
        int LoadTextureFromFile(string path) {
            Bitmap bmp = (Bitmap)Image.FromFile(path);            
            BitmapData bmp_data = bmp.LockBits(new Rectangle(0, 0, bmp.Width, bmp.Height), System.Drawing.Imaging.ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
            GL.GenTextures(1, out int textureID);
            GL.BindTexture(TextureTarget.Texture2D, textureID);
            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba, bmp.Width, bmp.Height, 0, OpenTK.Graphics.OpenGL4.PixelFormat.Bgra, PixelType.UnsignedByte, bmp_data.Scan0);
            GL.GenerateMipmap(GenerateMipmapTarget.Texture2D);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapS, (int)OpenTK.Graphics.OpenGL4.TextureWrapMode.Repeat);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapT, (int)OpenTK.Graphics.OpenGL4.TextureWrapMode.Repeat);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.LinearMipmapLinear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);
            bmp.UnlockBits(bmp_data);
            return textureID;
        }
    };
    public class MyMesh {
        int VAO, VBO, EBO;
        List<Vertex> Vertices;
        List<int> Indices;
        List<Texture> Textures;

        public MyMesh(List<Vertex> _vertices, List<int> _indices, List<Texture> _textures) {
            Vertices = _vertices;
            Indices = _indices;
            Textures = _textures;
            GL.GenVertexArrays(1, out VAO);
            GL.GenBuffers(1, out VBO);
            GL.GenBuffers(1, out EBO);

            GL.BindVertexArray(VAO);
            GL.BindBuffer(BufferTarget.ArrayBuffer, VBO);
            GL.BufferData(BufferTarget.ArrayBuffer, Vertices.Count * 56, Vertices.ToArray(), BufferUsageHint.StaticDraw);
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, EBO);           
            GL.BufferData(BufferTarget.ElementArrayBuffer, Indices.Count * 4, Indices.ToArray(), BufferUsageHint.StaticDraw);
            GL.EnableVertexAttribArray(0);
            GL.VertexAttribPointer(0, 3, VertexAttribPointerType.Float, false, 56, 0);
            GL.EnableVertexAttribArray(1);
            GL.VertexAttribPointer(1, 3, VertexAttribPointerType.Float, false, 56, 12);
            GL.EnableVertexAttribArray(2);
            GL.VertexAttribPointer(2, 2, VertexAttribPointerType.Float, false, 56, 24);
            GL.EnableVertexAttribArray(3);
            GL.VertexAttribPointer(3, 3, VertexAttribPointerType.Float, false, 56, 32);
            GL.EnableVertexAttribArray(4);
            GL.VertexAttribPointer(4, 3, VertexAttribPointerType.Float, false, 56, 44);

            GL.BindVertexArray(0);
        }
        public void Draw(Shader shader) {
            uint diffuseNr = 1, specularNr = 1;
            for (int i = 0; i < Textures.Count; i++) {
                GL.ActiveTexture(TextureUnit.Texture0 + i);
                string name = Textures[i].type;
                string number = (name == "texture_diffuse") ? (diffuseNr++).ToString() : (specularNr++).ToString();
                
                shader.SetInt("material." + name + number, i);
                GL.BindTexture(TextureTarget.Texture2D, Textures[i].id);
            }
            GL.BindVertexArray(VAO);
            GL.DrawElements(BeginMode.Triangles, Indices.Count, DrawElementsType.UnsignedInt, 0);
            GL.BindVertexArray(0);
            GL.ActiveTexture(TextureUnit.Texture0);
        }
    }
};