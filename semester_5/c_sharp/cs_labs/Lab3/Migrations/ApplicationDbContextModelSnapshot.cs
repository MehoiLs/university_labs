﻿// <auto-generated />
using System;
using Lab3.Context;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using Npgsql.EntityFrameworkCore.PostgreSQL.Metadata;

#nullable disable

namespace Lab3.Migrations
{
    [DbContext(typeof(ApplicationDbContext))]
    partial class ApplicationDbContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "9.0.0-rc.2.24474.1")
                .HasAnnotation("Relational:MaxIdentifierLength", 63);

            NpgsqlModelBuilderExtensions.UseIdentityByDefaultColumns(modelBuilder);

            modelBuilder.Entity("HotelHotelOffering", b =>
                {
                    b.Property<long>("HotelsId")
                        .HasColumnType("bigint");

                    b.Property<long>("OfferingsId")
                        .HasColumnType("bigint");

                    b.HasKey("HotelsId", "OfferingsId");

                    b.HasIndex("OfferingsId");

                    b.ToTable("HotelHotelOffering");
                });

            modelBuilder.Entity("HotelOfferingServiceInvoice", b =>
                {
                    b.Property<long>("InvoicesId")
                        .HasColumnType("bigint");

                    b.Property<long>("ServicesId")
                        .HasColumnType("bigint");

                    b.HasKey("InvoicesId", "ServicesId");

                    b.HasIndex("ServicesId");

                    b.ToTable("HotelOfferingServiceInvoice");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Hotel", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<string>("Address")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<double>("Area")
                        .HasColumnType("double precision");

                    b.Property<string>("Email")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<string>("Name")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<long>("OwnerId")
                        .HasColumnType("bigint");

                    b.Property<string>("Phone")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<DateTime>("YearOpenedIn")
                        .HasColumnType("timestamp with time zone");

                    b.HasKey("Id");

                    b.HasIndex("OwnerId");

                    b.ToTable("Hotels");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.HotelKeyCard", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<long?>("ClientId")
                        .HasColumnType("bigint");

                    b.Property<long>("HotelId")
                        .HasColumnType("bigint");

                    b.Property<DateTime?>("LastAssignedAt")
                        .HasColumnType("timestamp with time zone");

                    b.HasKey("Id");

                    b.HasIndex("ClientId")
                        .IsUnique();

                    b.HasIndex("HotelId");

                    b.ToTable("KeyCards");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.HotelOffering", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<double>("AveragePrice")
                        .HasColumnType("double precision");

                    b.Property<string>("Description")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<string>("Name")
                        .IsRequired()
                        .HasColumnType("text");

                    b.HasKey("Id");

                    b.ToTable("Services");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Invoices.Fee", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<double>("Cash")
                        .HasColumnType("double precision");

                    b.Property<long>("ClientId")
                        .HasColumnType("bigint");

                    b.Property<DateTime>("CreatedAt")
                        .HasColumnType("timestamp with time zone");

                    b.Property<int>("Type")
                        .HasColumnType("integer");

                    b.HasKey("Id");

                    b.HasIndex("ClientId");

                    b.ToTable("Fees");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Invoices.Invoice", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<double>("Cash")
                        .HasColumnType("double precision");

                    b.Property<long>("ClientId")
                        .HasColumnType("bigint");

                    b.Property<DateTime>("CreatedAt")
                        .HasColumnType("timestamp with time zone");

                    b.Property<string>("Discriminator")
                        .IsRequired()
                        .HasMaxLength(21)
                        .HasColumnType("character varying(21)");

                    b.Property<int>("Type")
                        .HasColumnType("integer");

                    b.HasKey("Id");

                    b.HasIndex("ClientId");

                    b.ToTable("Invoices");

                    b.HasDiscriminator().HasValue("Invoice");

                    b.UseTphMappingStrategy();
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.People.Client", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<string>("FullName")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<long>("HotelId")
                        .HasColumnType("bigint");

                    b.Property<string>("Passport")
                        .IsRequired()
                        .HasColumnType("text");

                    b.HasKey("Id");

                    b.HasIndex("HotelId");

                    b.ToTable("Clients");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.People.Employee", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<DateTime>("BirthDate")
                        .HasColumnType("timestamp with time zone");

                    b.Property<string>("FullName")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<long>("HotelId")
                        .HasColumnType("bigint");

                    b.Property<long>("OccupationId")
                        .HasColumnType("bigint");

                    b.Property<string>("Passport")
                        .IsRequired()
                        .HasColumnType("text");

                    b.HasKey("Id");

                    b.HasIndex("HotelId");

                    b.HasIndex("OccupationId");

                    b.ToTable("Employees");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.People.Occupation", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<long>("Salary")
                        .HasColumnType("bigint");

                    b.Property<int>("Type")
                        .HasColumnType("integer");

                    b.HasKey("Id");

                    b.ToTable("Occupations");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.People.Owner", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<string>("FullName")
                        .IsRequired()
                        .HasColumnType("text");

                    b.HasKey("Id");

                    b.ToTable("Owners");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Rooms.Room", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<int>("Floor")
                        .HasColumnType("integer");

                    b.Property<long>("PropertiesId")
                        .HasColumnType("bigint");

                    b.Property<long>("RoomNumber")
                        .HasColumnType("bigint");

                    b.HasKey("Id");

                    b.HasIndex("PropertiesId");

                    b.ToTable("Rooms");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Rooms.RoomFeature", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<long?>("BookingId")
                        .HasColumnType("bigint");

                    b.Property<string>("Description")
                        .HasColumnType("text");

                    b.Property<string>("Name")
                        .IsRequired()
                        .HasColumnType("text");

                    b.HasKey("Id");

                    b.HasIndex("BookingId");

                    b.ToTable("RoomFeatures");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Rooms.RoomPriceRate", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<int>("PricePerNight")
                        .HasColumnType("integer");

                    b.Property<long>("PropertiesId")
                        .HasColumnType("bigint");

                    b.Property<DateTime>("StartDate")
                        .HasColumnType("timestamp with time zone");

                    b.HasKey("Id");

                    b.HasIndex("PropertiesId");

                    b.ToTable("RoomPriceRates");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Rooms.RoomProperties", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<int>("Class")
                        .HasColumnType("integer");

                    b.Property<long>("HotelId")
                        .HasColumnType("bigint");

                    b.Property<int>("Size")
                        .HasColumnType("integer");

                    b.HasKey("Id");

                    b.HasIndex("HotelId");

                    b.ToTable("RoomProperties");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Stays.Booking", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<DateTime>("CheckingInAt")
                        .HasColumnType("timestamp with time zone");

                    b.Property<DateTime>("CheckingOutAt")
                        .HasColumnType("timestamp with time zone");

                    b.Property<long>("ClientId")
                        .HasColumnType("bigint");

                    b.PrimitiveCollection<int[]>("PreferredRoomClasses")
                        .HasColumnType("integer[]");

                    b.PrimitiveCollection<int[]>("PreferredRoomSizes")
                        .HasColumnType("integer[]");

                    b.HasKey("Id");

                    b.HasIndex("ClientId");

                    b.ToTable("Bookings");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Stays.Staying", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<DateTime>("CheckedInAt")
                        .HasColumnType("timestamp with time zone");

                    b.Property<DateTime>("CheckedOutAt")
                        .HasColumnType("timestamp with time zone");

                    b.Property<long>("ClientId")
                        .HasColumnType("bigint");

                    b.Property<long>("RoomId")
                        .HasColumnType("bigint");

                    b.HasKey("Id");

                    b.HasIndex("ClientId");

                    b.HasIndex("RoomId");

                    b.ToTable("Stayings");
                });

            modelBuilder.Entity("RoomFeatureRoomProperties", b =>
                {
                    b.Property<long>("FeaturesId")
                        .HasColumnType("bigint");

                    b.Property<long>("PropertiesId")
                        .HasColumnType("bigint");

                    b.HasKey("FeaturesId", "PropertiesId");

                    b.HasIndex("PropertiesId");

                    b.ToTable("RoomFeatureRoomProperties");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Invoices.LivingInvoice", b =>
                {
                    b.HasBaseType("Lab3.Entity.Hotel.Invoices.Invoice");

                    b.Property<long>("StayingId")
                        .HasColumnType("bigint");

                    b.HasIndex("StayingId");

                    b.HasDiscriminator().HasValue("LivingInvoice");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Invoices.ServiceInvoice", b =>
                {
                    b.HasBaseType("Lab3.Entity.Hotel.Invoices.Invoice");

                    b.HasDiscriminator().HasValue("ServiceInvoice");
                });

            modelBuilder.Entity("HotelHotelOffering", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.Hotel", null)
                        .WithMany()
                        .HasForeignKey("HotelsId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("Lab3.Entity.Hotel.HotelOffering", null)
                        .WithMany()
                        .HasForeignKey("OfferingsId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();
                });

            modelBuilder.Entity("HotelOfferingServiceInvoice", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.Invoices.ServiceInvoice", null)
                        .WithMany()
                        .HasForeignKey("InvoicesId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("Lab3.Entity.Hotel.HotelOffering", null)
                        .WithMany()
                        .HasForeignKey("ServicesId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Hotel", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.People.Owner", "Owner")
                        .WithMany("Hotels")
                        .HasForeignKey("OwnerId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Owner");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.HotelKeyCard", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.People.Client", "Client")
                        .WithOne("KeyCard")
                        .HasForeignKey("Lab3.Entity.Hotel.HotelKeyCard", "ClientId");

                    b.HasOne("Lab3.Entity.Hotel.Hotel", "Hotel")
                        .WithMany("KeyCards")
                        .HasForeignKey("HotelId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Client");

                    b.Navigation("Hotel");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Invoices.Fee", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.People.Client", "Client")
                        .WithMany()
                        .HasForeignKey("ClientId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Client");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Invoices.Invoice", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.People.Client", "Client")
                        .WithMany()
                        .HasForeignKey("ClientId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Client");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.People.Client", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.Hotel", "Hotel")
                        .WithMany()
                        .HasForeignKey("HotelId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Hotel");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.People.Employee", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.Hotel", "Hotel")
                        .WithMany()
                        .HasForeignKey("HotelId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("Lab3.Entity.Hotel.People.Occupation", "Occupation")
                        .WithMany()
                        .HasForeignKey("OccupationId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Hotel");

                    b.Navigation("Occupation");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Rooms.Room", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.Rooms.RoomProperties", "Properties")
                        .WithMany()
                        .HasForeignKey("PropertiesId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Properties");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Rooms.RoomFeature", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.Stays.Booking", null)
                        .WithMany("PreferredRoomFeatures")
                        .HasForeignKey("BookingId");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Rooms.RoomPriceRate", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.Rooms.RoomProperties", "Properties")
                        .WithMany()
                        .HasForeignKey("PropertiesId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Properties");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Rooms.RoomProperties", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.Hotel", "Hotel")
                        .WithMany()
                        .HasForeignKey("HotelId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Hotel");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Stays.Booking", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.People.Client", "Client")
                        .WithMany()
                        .HasForeignKey("ClientId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Client");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Stays.Staying", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.People.Client", "Client")
                        .WithMany()
                        .HasForeignKey("ClientId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("Lab3.Entity.Hotel.Rooms.Room", "Room")
                        .WithMany()
                        .HasForeignKey("RoomId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Client");

                    b.Navigation("Room");
                });

            modelBuilder.Entity("RoomFeatureRoomProperties", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.Rooms.RoomFeature", null)
                        .WithMany()
                        .HasForeignKey("FeaturesId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("Lab3.Entity.Hotel.Rooms.RoomProperties", null)
                        .WithMany()
                        .HasForeignKey("PropertiesId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Invoices.LivingInvoice", b =>
                {
                    b.HasOne("Lab3.Entity.Hotel.Stays.Staying", "Staying")
                        .WithMany()
                        .HasForeignKey("StayingId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Staying");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Hotel", b =>
                {
                    b.Navigation("KeyCards");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.People.Client", b =>
                {
                    b.Navigation("KeyCard");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.People.Owner", b =>
                {
                    b.Navigation("Hotels");
                });

            modelBuilder.Entity("Lab3.Entity.Hotel.Stays.Booking", b =>
                {
                    b.Navigation("PreferredRoomFeatures");
                });
#pragma warning restore 612, 618
        }
    }
}
